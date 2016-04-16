/*
 * Copyright (C) 2016 Dmitry Marakasov
 *
 * This file is part of donatallo.
 *
 * donatallo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * donatallo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with donatallo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libdonatallo/database.hh>

#include <iostream>

#include <yaml-cpp/yaml.h>

#include <libdonatallo/detectorchain.hh>

namespace Donatallo {

Database::ParsingException::ParsingException(const std::string& file, int line, int column, const std::string& msg)
	: std::runtime_error(build_what(file, line, column, msg)),
	  file_(file),
	  line_(line),
	  column_(column),
	  msg_(file) {
}

std::string Database::ParsingException::build_what(const std::string& file, int line, int column, const std::string& msg) {
	std::stringstream output;
	output << file;

	if (line >= 0) {
		output << ":" << line + 1;
		if (column >= 0)
			output << ":" << column + 1;
	}

	output << ": " << msg;

	return output.str();
}

Database::Database() {
}

void Database::LoadFile(const std::string& path, const std::string& filename) {
	YAML::Node data = YAML::LoadFile(path + "/" + filename);

	if (!data.IsSequence())
		throw std::runtime_error("bad database format (should be a sequence)");

	int num_entry = 1;

	for (const auto& entry : data) {
		if (!entry["name"].IsDefined() || !entry["name"].IsScalar())
			throw std::runtime_error(filename + ", entry #" + std::to_string(num_entry) + ": name missing or is not defined");

		if (!entry["description"].IsDefined() || !entry["description"].IsScalar())
			throw std::runtime_error(filename + ", entry #" + std::to_string(num_entry) + ": description missing or is not defined");

		if (!entry["url"].IsDefined() || !entry["url"].IsScalar())
			throw std::runtime_error(filename + ", entry #" + std::to_string(num_entry) + ": url missing or is not defined");

		Project proj;

		proj.name = entry["name"].Scalar();
		proj.description = entry["description"].Scalar();
		proj.url = entry["url"].Scalar();

		projects_.emplace_back(std::move(proj));

		num_entry++;
	}
}

void Database::Load(const std::string& path) {
	YAML::Node meta = YAML::LoadFile(path + "/meta.yml");

	if (!meta.IsMap())
		throw std::runtime_error("bad u metadata format (meta.yml should be a map)");

	if (!meta["version"].IsDefined() || !meta["version"].IsScalar())
		throw std::runtime_error("bad database metadata format (version missing)");

	std::string version = meta["version"].Scalar();

	// version check
	{
		const int my_major = 1;
		const int my_minor = 0;

		size_t dot1pos = version.find('.');
		if (dot1pos == std::string::npos)
			throw std::runtime_error("bad database metadata format (bad version format)");
		size_t dot2pos = version.find('.', dot1pos + 1);
		if (dot2pos == std::string::npos)
			throw std::runtime_error("bad database metadata format (bad version format)");

		int major = std::stoi(version.substr(0, dot1pos));
		int minor = std::stoi(version.substr(dot1pos + 1, dot2pos - dot1pos - 1));
		int patch = std::stoi(version.substr(dot2pos + 1));

		if (major > my_major)
			throw std::runtime_error("database major version too new, not supported; please update donatallo");
		if (major < my_major)
			throw std::runtime_error("database major version too old, not supported; please update the database");

		if (minor > my_minor)
			std::cerr << "Warning: database minor version is newer than known to an application, which means that some database features may be unsupported" << std::endl;
	}

	if (!meta["files"].IsDefined()) {
		std::cerr << "Warning: database is empty" << std::endl;
		return;
	}

	if (!meta["files"].IsSequence())
		throw std::runtime_error("bad database metadata format (files should be a sequence)");

	for (const auto& file : meta["files"])
		LoadFile(path, file.Scalar());
}

Result Database::GetAll() const {
	Result res;

	for (const auto& project: projects_)
		res.Add(&project);

	return res;
}

Result Database::Query(const DetectorChain& detectors) const {
	Result res;

	for (const auto& project: projects_)
		if (detectors.Check(project))
			res.Add(&project);

	return res;
}

}
