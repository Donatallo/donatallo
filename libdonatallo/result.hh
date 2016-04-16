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

#ifndef DONATALLO_RESULT_HH
#define DONATALLO_RESULT_HH

namespace Donatallo {

class Project;

class Result {
public:
	enum class SortCriteria {
		NAME,
	};

private:
	std::vector<const Project*> results_;

public:
	Result();

	void Add(const Project* project);

	Result Sort(SortCriteria criteria = SortCriteria::NAME, bool ascending = true) const;

	size_t size() const;
	bool empty() const;
	const Project& operator[](size_t pos) const;

	const Project* begin() const {
		return *results_.cbegin();
	}

	const Project* cbegin() const {
		return *results_.cbegin();
	}

	const Project* end() const {
		return *results_.cend();
	}

	const Project* cend() const {
		return *results_.cend();
	}
};

}

#endif
