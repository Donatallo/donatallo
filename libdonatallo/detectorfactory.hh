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

#ifndef DONATALLO_DETECTORFACTORY_HH
#define DONATALLO_DETECTORFACTORY_HH

#include <memory>
#include <vector>
#include <functional>

#include <libdonatallo/detectorchain.hh>

namespace Donatallo {

class Detector;

class DetectorFactory {
private:
	typedef std::function<void(DetectorChain&)> DetectorChainAppenderFunction;

private:
	static DetectorFactory* instance_;
	std::vector<DetectorChainAppenderFunction> appenders_;

public:
	template <class T>
	class Registrar {
	public:
		Registrar() {
			DetectorFactory::GetInstance()->Register<T>();
		}
	};

private:
	DetectorFactory();

	template<class T>
	void Register() {
		appenders_.emplace_back([](DetectorChain& chain){ chain.Append<T>(); });
	}

public:
	static DetectorFactory* GetInstance();

	DetectorChain GetAllDetectors() const;
};

}

#endif
