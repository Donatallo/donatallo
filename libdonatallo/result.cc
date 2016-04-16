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

#include <libdonatallo/result.hh>

namespace Donatallo {

Result::Result() {
}

void Result::Add(const Project* project) {
	results_.push_back(project);
}

//Result Result::Sort(SortCriteria criteria = SortCriteria::NAME, bool ascending = true) const {
//	return this;
//}

size_t Result::size() const {
	return results_.size();
}

bool Result::empty() const {
	return results_.empty();
}

const Project& Result::operator[](size_t pos) const {
	return *results_[pos];
}

const Project* Result::begin() const {
	return *results_.cbegin();
}

const Project* Result::cbegin() const {
	return *results_.cbegin();
}

const Project* Result::end() const {
	return *results_.cend();
}

const Project* Result::cend() const {
	return *results_.cend();
}

}
