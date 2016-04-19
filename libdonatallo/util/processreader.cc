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

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include <system_error>

namespace Donatallo {

ProcessReader::ProcessReader() {
}

ProcessReader::StringVector ProcessReader::ReadAllWords(int fd) {
	char buffer[65536];

	std::string current;

	StringVector strings;

	while (1) {
		ssize_t nread = read(fd, buffer, sizeof(buffer));
		if (nread == 0) // eof
			break;
		else if (nread == -1 && errno == EINTR) // interrupted system call
			continue;
		else if (nread == -1) // read error
			throw std::system_error(errno, std::system_category());

		for (char* ch = buffer; ch != buffer + nread; ch++) {
			switch (*ch) {
			case ' ': case '\n': case '\t': case '\r':
				if (!current.empty()) {
					strings.push_back(current);
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
		strings.push_back(current);

	return strings;
}

std::pair<pid_t, int> ProcessReader::ForkChild(const char* path, char* const* argv) {
	int pipefd[2];

	// pipe
	if (pipe(pipefd) != 0)
		throw std::system_error(errno, std::system_category());

	// fork
	pid_t childpid = fork();
	if (childpid == -1) {
		int saved_errno = errno;
		close(pipefd[0]);
		close(pipefd[1]);
		throw std::system_error(saved_errno, std::system_category());
	}

	if (childpid == 0) {
		// child
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);

#ifdef HAVE_CLOSEFROM
		closefrom(3);
#else
		// this may be slow, e.g. on FreeBSD getdtablesize() returns 170k+
		for (int fd = 3; fd < getdtablesize(); fd++)
			close(fd);
#endif

		sigset_t mask;
		sigfillset(&mask);
		sigprocmask(SIG_UNBLOCK, &mask, nullptr);

		execv(path, argv);
		exit(1); // if exec fails
	}

	// parent
	close(pipefd[1]);

	return std::make_pair(childpid, pipefd[0]);
}

int ProcessReader::WaitForPid(pid_t pid) {
	int status;

	while (1) {
		if (waitpid(pid, &status, 0) == -1) {
			if (errno == EINTR) // interrupted system call
				continue;
			else // error
				throw std::system_error(errno, std::system_category());
		}

		// only want process termination statuses
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return WEXITSTATUS(status);
	}
}

bool ProcessReader::Run(const char* path, char* const* argv) {
	int readfd;
	pid_t childpid;
	std::tie(childpid, readfd) = ForkChild(path, argv);

	StringVector temp;

	try {
		temp = ReadAllWords(readfd);
	} catch (...) {
		WaitForPid(childpid);
		close(readfd);
		throw;
	}

	close(readfd);

	if (WaitForPid(childpid) == 0) {
		for (const auto& word : temp)
			output_.insert(word);
		return true;
	}

	return false;
}

bool ProcessReader::RunScript(const std::string& path) {
	const char* const argv[] = { "/bin/sh", path.c_str(), nullptr };
	return Run("/bin/sh", const_cast<char* const*>(argv));
}

bool ProcessReader::RunShell(const std::string& commandline) {
	const char* const argv[] = { "/bin/sh", "-c", commandline.c_str(), nullptr };
	return Run("/bin/sh", const_cast<char* const*>(argv));
}

const ProcessReader::StringSet& ProcessReader::GetOutput() const {
	return output_;
}

}
