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

#ifndef DONATALLO_PROJECT_HH
#define DONATALLO_PROJECT_HH

#include <string>
#include <map>
#include <vector>

namespace Donatallo {

class DonationVisitor;

class Project {
public:
	typedef std::vector<std::string> DetectionTagVector;
	typedef std::map<std::string, DetectionTagVector> DetectionTagMap;

	std::string name;
	std::string comment;
	std::string url;

	DetectionTagMap detection_tags;
};

}

#endif
