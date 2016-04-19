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
	if (method == "cheque")
		return DonationMethod::CHEQUE;
	if (method == "yandex_money")
		return DonationMethod::YANDEX_MONEY;
	if (method == "flattr")
		return DonationMethod::FLATTR;
	if (method == "clickandpledge")
		return DonationMethod::CLICKANDPLEDGE;
	if (method == "merchandise")
		return DonationMethod::MERCHANDISE;
	if (method == "litecoin")
		return DonationMethod::LITECOIN;
	if (method == "patreon")
		return DonationMethod::PATREON;
	if (method == "bountysource")
		return DonationMethod::BOUNTYSOURCE;
	return DonationMethod::UNKNOWN;
}

std::string Project::DonationMethodToKeyword(DonationMethod method) {
	switch (method) {
	case DonationMethod::PAYPAL:
		return "paypal";
	case DonationMethod::BITCOIN:
		return "bitcoin";
	case DonationMethod::BANK_TRANSFER:
		return "bank_transfer";
	case DonationMethod::CHEQUE:
		return "cheque";
	case DonationMethod::YANDEX_MONEY:
		return "yandex_money";
	case DonationMethod::FLATTR:
		return "flattr";
	case DonationMethod::CLICKANDPLEDGE:
		return "clickandpledge";
	case DonationMethod::MERCHANDISE:
		return "merchandise";
	case DonationMethod::LITECOIN:
		return "litecoin";
	case DonationMethod::PATREON:
		return "patreon";
	case DonationMethod::BOUNTYSOURCE:
		return "bountysource";
	default:
		throw std::logic_error("unknown donation method");
	}
}

std::string Project::DonationMethodToHumanReadable(DonationMethod method) {
	switch (method) {
	case DonationMethod::PAYPAL:
		return "PayPal";
	case DonationMethod::BITCOIN:
		return "Bitcoin";
	case DonationMethod::BANK_TRANSFER:
		return "Bank transfer";
	case DonationMethod::CHEQUE:
		return "Cheque";
	case DonationMethod::YANDEX_MONEY:
		return "Yandex.Money";
	case DonationMethod::FLATTR:
		return "Flattr";
	case DonationMethod::CLICKANDPLEDGE:
		return "Click & Pledge";
	case DonationMethod::MERCHANDISE:
		return "Merchandise";
	case DonationMethod::LITECOIN:
		return "Litecoin";
	case DonationMethod::PATREON:
		return "Patreon";
	case DonationMethod::BOUNTYSOURCE:
		return "Bountysource";
	default:
		throw std::logic_error("unknown donation method");
	}
}

void Project::ForEachDonationMethod(std::function<void(DonationMethod)>&& handler) {
	handler(DonationMethod::BANK_TRANSFER);
	handler(DonationMethod::BITCOIN);
	handler(DonationMethod::BOUNTYSOURCE);
	handler(DonationMethod::CHEQUE);
	handler(DonationMethod::CLICKANDPLEDGE);
	handler(DonationMethod::FLATTR);
	handler(DonationMethod::LITECOIN);
	handler(DonationMethod::MERCHANDISE);
	handler(DonationMethod::PATREON);
	handler(DonationMethod::PAYPAL);
	handler(DonationMethod::YANDEX_MONEY);
}

}
