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

#ifndef DONATALLO_DETECTORCHAIN_HH
#define DONATALLO_DETECTORCHAIN_HH

#include <memory>
#include <vector>
#include <functional>

namespace Donatallo {

class Detector;
class Project;

class DetectorChain {
private:
	std::vector<std::unique_ptr<Detector>> detectors_;

public:
	typedef std::function<void(int, int)> StatusCallback;

public:
	DetectorChain();
	~DetectorChain();

	DetectorChain(const DetectorChain&) = delete;
	DetectorChain(DetectorChain&&);
	DetectorChain& operator=(const DetectorChain&) = delete;
	DetectorChain& operator=(DetectorChain&&);

	template<class T>
	void Append() {
		std::unique_ptr<T> detector(new T);
		detectors_.emplace_back(std::move(detector));
	}

	void Prepare(StatusCallback&& status_callback = StatusCallback());
	bool Check(const Project& project) const;
};

}

#endif
