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

#ifndef DONATALLO_DATABASE_HH
#define DONATALLO_DATABASE_HH

#include <string>
#include <stdexcept>

#include <libdonatallo/detector.hh>
#include <libdonatallo/project.hh>
#include <libdonatallo/donationmethod.hh>
#include <libdonatallo/result.hh>

namespace Donatallo {

class DetectorChain;

class Database {
public:
	class ParsingException : public std::runtime_error {
	private:
		std::string file_;
		int line_, column_;
		std::string msg_;

	public:
		ParsingException(const std::string& file, int line, int column, const std::string& msg);

		static std::string build_what(const std::string& file, int line, int column, const std::string& msg);
	};

	enum QueryFlags {
		INVERT_DETECTION = 1,
	};

private:
	std::vector<Project> projects_;
	std::map<std::string, DonationMethod> methods_;

private:
	void LoadMeta(const std::string& path, std::vector<std::string>& method_files_to_load, std::vector<std::string>& project_files_to_load);
	void LoadMethods(const std::string& path);
	void LoadProjects(const std::string& path);

public:
	Database();

	void Load(const std::string& dbdir);

	Result GetAll() const;
	Result Query(const DetectorChain& detectors, int flags = 0) const;

	size_t size() const;

	bool HasDonationMethod(const std::string& keyword) const;
	const DonationMethod& GetDonationMethod(const std::string& keyword) const;
	void ForEachDonationMethod(std::function<void(const DonationMethod&)>&& handler) const;
};

}

#endif
