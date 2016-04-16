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

#include <cassert>

#include <yaml-cpp/yaml.h>

#include <libdonatallo/detectorchain.hh>

namespace Donatallo {

Database::Database() {
}

void Database::Load(const std::string& path) {
	YAML::Node database = YAML::LoadFile(path + "/meta.yml");
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
