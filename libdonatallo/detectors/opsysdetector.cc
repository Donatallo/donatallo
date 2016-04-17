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

#include <libdonatallo/detectors/opsysdetector.hh>

#include <libdonatallo/project.hh>
#include <libdonatallo/detectorfactory.hh>

namespace Donatallo {

OpsysDetector::~OpsysDetector() {
}

void OpsysDetector::Prepare() {
}

bool OpsysDetector::Check(const Project& project) const {
	const auto tag = project.detection_tags.find("opsys");

	if (tag == project.detection_tags.end())
		return false;

	for (const auto& keyword : tag->second) {
#if defined(__FreeBSD__)
		if (keyword == "FreeBSD")
			return true;
#endif
#if defined(__NetBSD__)
		if (keyword == "NetBSD")
			return true;
#endif
#if defined(__OpenBSD__)
		if (keyword == "OpenBSD")
			return true;
#endif
#if defined(__DragonFly__)
		if (keyword == "DragonFly")
			return true;
#endif
#if defined(__linux__)
		if (keyword == "Linux")
			return true;
#endif
		// XXX: more systems to be added, we may even need
		// non-free ones to be used in conditions (e.g.
		// opsys == Windows && pkgname == ...) when these
		// are implemented
	}

	return false;
}

static DetectorFactory::Registrar<OpsysDetector> registrar;

}
