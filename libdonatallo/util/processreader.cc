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

#include <libdonatallo/util/processreader.hh>

#include <stdio.h>

namespace Donatallo {

ProcessReader::ProcessReader() {
}

bool ProcessReader::Run(const std::string& commandline) {
	FILE *f = popen(commandline.c_str(), "r");
	if (f == nullptr)
		return false;

	static constexpr size_t bufsize = 65536;

	char buffer[bufsize];

	std::string current;

	try {
		while (1) {
			size_t nread = fread(buffer, 1, bufsize, f);
			if (nread == 0 && feof(f))
				break;
			else if (nread == 0)
				throw std::runtime_error("error reading from process");

			for (char* ch = buffer; ch != buffer + nread; ch++) {
				switch (*ch) {
				case ' ': case '\n': case '\t': case '\r':
					if (!current.empty()) {
						output_.insert(current);
						current.clear();
					}
					break;
				default:
					current += *ch;
					break;
				}
			}
		}

		if (!current.empty())
			output_.insert(current);
	} catch (...) {
		pclose(f);
		throw;
	}

	return pclose(f) != -1;
}

const ProcessReader::ResultsSet& ProcessReader::GetOutput() const {
	return output_;
}

}
