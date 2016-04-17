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

#include <libdonatallo/detectors/packagedetector.hh>

#include <libdonatallo/project.hh>
#include <libdonatallo/util/processreader.hh>
#include <libdonatallo/detectorfactory.hh>

namespace Donatallo {

PackageDetector::~PackageDetector() {
}

void PackageDetector::Prepare() {
	ProcessReader proc;
	if (proc.Run(DONATALLO_DATADIR "/scripts/list-packages.sh")) {
		for (const auto& package : proc.GetOutput())
			packages_.insert(package);
	}
}

bool PackageDetector::Check(const Project& project) const {
	const auto tag = project.detection_tags.find("pkgnames");

	if (tag == project.detection_tags.end())
		return false;

	for (const auto& keyword : tag->second) {
		if (packages_.find(keyword) != packages_.end())
			return true;
	}

	return false;
}

static DetectorFactory::Registrar<PackageDetector> registrar;

}
