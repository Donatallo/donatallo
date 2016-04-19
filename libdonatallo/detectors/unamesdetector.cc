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

#include <libdonatallo/detectors/unamesdetector.hh>

#include <libdonatallo/project.hh>
#include <libdonatallo/util/processreader.hh>
#include <libdonatallo/detectorfactory.hh>

namespace Donatallo {

UnameSDetector::~UnameSDetector() {
}

void UnameSDetector::Prepare() {
	ProcessReader proc;
	if (proc.RunShell("uname -s")) {
		const auto output = proc.GetOutput();
		if (!output.empty())
			uname_s_ = *output.begin();
	}
}

bool UnameSDetector::Check(const Project& project) const {
	if (uname_s_.empty())
		return false;

	const auto tag = project.detection_tags.find("uname-s");

	if (tag == project.detection_tags.end())
		return false;

	for (const auto& uname : tag->second) {
		if (uname == uname_s_)
			return true;
	}

	return false;
}

static DetectorFactory::Registrar<UnameSDetector> registrar;

}
