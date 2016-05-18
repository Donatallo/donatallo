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
	if (method == "dwolla")
		return DonationMethod::DWOLLA;
	if (method == "amazon")
		return DonationMethod::AMAZON;
	if (method == "credit_card")
		return DonationMethod::CREDIT_CARD;
	if (method == "hardware")
		return DonationMethod::HARDWARE;
	if (method == "stripe")
		return DonationMethod::STRIPE;
	if (method == "pledgie")
		return DonationMethod::PLEDGIE;
	if (method == "webmoney")
		return DonationMethod::WEBMONEY;
	if (method == "western_union")
		return DonationMethod::WESTERN_UNION;
	if (method == "tibit")
		return DonationMethod::TIBIT;
	if (method == "dash")
		return DonationMethod::DASH;
	if (method == "anoncoin")
		return DonationMethod::ANONCOIN;
	if (method == "monero")
		return DonationMethod::MONERO;
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
	case DonationMethod::DWOLLA:
		return "dwolla";
	case DonationMethod::AMAZON:
		return "amazon";
	case DonationMethod::CREDIT_CARD:
		return "credit_card";
	case DonationMethod::HARDWARE:
		return "hardware";
	case DonationMethod::STRIPE:
		return "stripe";
	case DonationMethod::PLEDGIE:
		return "pledgie";
	case DonationMethod::WEBMONEY:
		return "webmoney";
	case DonationMethod::WESTERN_UNION:
		return "western_union";
	case DonationMethod::TIBIT:
		return "tibit";
	case DonationMethod::DASH:
		return "dash";
	case DonationMethod::ANONCOIN:
		return "anoncoin";
	case DonationMethod::MONERO:
		return "monero";
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
	case DonationMethod::DWOLLA:
		return "Dwolla";
	case DonationMethod::AMAZON:
		return "Amazon Payments";
	case DonationMethod::CREDIT_CARD:
		return "Credit Card";
	case DonationMethod::HARDWARE:
		return "Hardware donation";
	case DonationMethod::STRIPE:
		return "Stripe";
	case DonationMethod::PLEDGIE:
		return "Pledgie";
	case DonationMethod::WEBMONEY:
		return "WebMoney";
	case DonationMethod::WESTERN_UNION:
		return "Western Union";
	case DonationMethod::TIBIT:
		return "Tibit";
	case DonationMethod::DASH:
		return "Dash";
	case DonationMethod::ANONCOIN:
		return "Anoncoin";
	case DonationMethod::MONERO:
		return "Monero";
	default:
		throw std::logic_error("unknown donation method");
	}
}

void Project::ForEachDonationMethod(std::function<void(DonationMethod)>&& handler) {
	handler(DonationMethod::AMAZON);
	handler(DonationMethod::ANONCOIN);
	handler(DonationMethod::BANK_TRANSFER);
	handler(DonationMethod::BITCOIN);
	handler(DonationMethod::BOUNTYSOURCE);
	handler(DonationMethod::CHEQUE);
	handler(DonationMethod::CLICKANDPLEDGE);
	handler(DonationMethod::CREDIT_CARD);
	handler(DonationMethod::DASH);
	handler(DonationMethod::DWOLLA);
	handler(DonationMethod::FLATTR);
	handler(DonationMethod::HARDWARE);
	handler(DonationMethod::LITECOIN);
	handler(DonationMethod::MERCHANDISE);
	handler(DonationMethod::MONERO);
	handler(DonationMethod::PATREON);
	handler(DonationMethod::PAYPAL);
	handler(DonationMethod::PLEDGIE);
	handler(DonationMethod::STRIPE);
	handler(DonationMethod::TIBIT);
	handler(DonationMethod::WEBMONEY);
	handler(DonationMethod::WESTERN_UNION);
	handler(DonationMethod::YANDEX_MONEY);
}

}
