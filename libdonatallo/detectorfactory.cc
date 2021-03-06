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

#include <libdonatallo/detectorfactory.hh>

namespace Donatallo {

DetectorFactory* DetectorFactory::instance_;

DetectorFactory::DetectorFactory() {
}

DetectorFactory* DetectorFactory::GetInstance() {
	if (instance_)
		return instance_;
	return instance_ = new DetectorFactory;
}

DetectorChain DetectorFactory::GetAllDetectors() const {
	DetectorChain chain;

	for (const auto& appender : appenders_)
		appender(chain);

	return chain;
}

}
