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

#include <string.h> // strcasecmp; no simple equivalent in c++

#include <algorithm>

#include <libdonatallo/result.hh>
#include <libdonatallo/project.hh>

namespace Donatallo {

Result::Result() {
}

void Result::Add(const Project* project) {
	results_.push_back(project);
}

Result Result::SortByName(bool ascending) const {
	Result result = *this;

	std::sort(result.results_.begin(), result.results_.end(),
		ascending ?
			[](const Project* a, const Project* b) {
				return strcasecmp(a->name.c_str(), b->name.c_str()) < 0;
			} :
			[](const Project* a, const Project* b) {
				return strcasecmp(a->name.c_str(), b->name.c_str()) > 0;
			}
	);

	return result;
}

size_t Result::size() const {
	return results_.size();
}

bool Result::empty() const {
	return results_.empty();
}

const Project& Result::operator[](size_t pos) const {
	return *results_[pos];
}

Result::const_iterator Result::begin() const {
	return results_.cbegin();
}

Result::const_iterator Result::end() const {
	return results_.cend();
}

Result::const_iterator Result::cbegin() const {
	return results_.cbegin();
}

Result::const_iterator Result::cend() const {
	return results_.cend();
}

}
