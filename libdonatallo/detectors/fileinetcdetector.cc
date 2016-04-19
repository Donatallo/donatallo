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

#include <libdonatallo/detectors/fileinetcdetector.hh>

#include <libdonatallo/project.hh>
#include <libdonatallo/util/processreader.hh>
#include <libdonatallo/detectorfactory.hh>

namespace Donatallo {

FileInEtcDetector::~FileInEtcDetector() {
}

void FileInEtcDetector::Prepare() {
	ProcessReader proc;
	if (proc.RunShell("ls /etc")) {
		for (const auto& file : proc.GetOutput())
			files_.insert(file);
	}
}

bool FileInEtcDetector::Check(const Project& project) const {
	const auto tag = project.detection_tags.find("file-in-etc");

	if (tag == project.detection_tags.end())
		return false;

	for (const auto& file : tag->second) {
		if (files_.find(file) != files_.end())
			return true;
	}

	return false;
}

static DetectorFactory::Registrar<FileInEtcDetector> registrar;

}
