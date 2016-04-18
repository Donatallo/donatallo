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

#include <libdonatallo/project.hh>

#include <stdexcept>

namespace Donatallo {

Project::DonationMethod Project::DonationMethodFromKeyword(const std::string& method) {
	if (method == "paypal")
		return DonationMethod::PAYPAL;
	if (method == "bitcoin")
		return DonationMethod::BITCOIN;
	if (method == "bank_transfer")
		return DonationMethod::BANK_TRANSFER;
	if (method == "yandex_money")
		return DonationMethod::YANDEX_MONEY;
	if (method == "flattr")
		return DonationMethod::FLATTR;
	if (method == "clickandpledge")
		return DonationMethod::CLICKANDPLEDGE;
	return DonationMethod::UNKNOWN;
}

std::string Project::DonationMethodToHumanReadable(DonationMethod method) {
	switch (method) {
	case DonationMethod::PAYPAL:
		return "PayPal";
	case DonationMethod::BITCOIN:
		return "BitCoin";
	case DonationMethod::BANK_TRANSFER:
		return "Bank transfer";
	case DonationMethod::YANDEX_MONEY:
		return "Yandex.Money";
	case DonationMethod::FLATTR:
		return "Flattr";
	case DonationMethod::CLICKANDPLEDGE:
		return "Click & Pledge";
	case DonationMethod::UNKNOWN:
		throw std::logic_error("unknown donation method");
	}
}

}
