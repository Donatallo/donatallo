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

#ifndef DONATALLO_PROCESSREADER_HH
#define DONATALLO_PROCESSREADER_HH

#include <unordered_set>
#include <vector>
#include <string>

namespace Donatallo {

class ProcessReader {
public:
	typedef std::vector<std::string> StringVector;
	typedef std::unordered_set<std::string> StringSet;

private:
	StringSet output_;

private:
	static StringVector ReadAllWords(int fd);
	std::pair<pid_t, int> ForkChild(const char* path, char* const* argv);
	static int WaitForPid(pid_t pid);

	bool Run(const char* path, char* const* argv);

public:
	ProcessReader();

	bool RunScript(const std::string& path);
	bool RunShell(const std::string& commandline);

	const StringSet& GetOutput() const;
};

}

#endif
