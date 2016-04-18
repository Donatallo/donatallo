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

#include <getopt.h>

#include <iostream>
#include <string>
#include <exception>

#include <libdonatallo/database.hh>
#include <libdonatallo/detectorfactory.hh>

static struct option longopts[] = {
	{ "all",       no_argument,       nullptr, 'a' },
	{ "database",  required_argument, nullptr, 'd' },
	{ "help",      no_argument,       nullptr, 'h' },
	{ nullptr,     0,                 nullptr, 0   },
};

void Usage(const std::string& progname, int exitstatus) {
	std::cerr << "Usage: " << progname << " [-ah] [-d database path]" << std::endl;
	std::cerr << std::endl;
	std::cerr << " -a, --all             list all projects in the database" << std::endl;
	std::cerr << " -d, --database=PATH   specify path to the database" << std::endl;
	std::cerr << " -h, --help            show this help" << std::endl;

	exit(exitstatus);
}

int main(int argc, char** argv) try {
	const std::string progname = argv[0];

	bool all_mode = false;
	std::string database_path = DONATALLO_DATADIR "/database";

	int ch;
	while ((ch = getopt_long(argc, argv, "ad:h", longopts, NULL)) != -1) {
		switch (ch) {
		case 'a':
			all_mode = true;
			break;
		case 'd':
			database_path = optarg;
			break;
		case 'h':
			Usage(progname, 0);
			break;
		default:
			Usage(progname, 1);
			break;
		}
	}

	// Load database
	Donatallo::Database db;
	db.Load(database_path);

	Donatallo::Result projects;

	// Query
	if (all_mode) {
		projects = db.GetAll();
	} else {
		Donatallo::DetectorChain detectors = Donatallo::DetectorFactory::GetInstance()->GetAllDetectors();

		detectors.Prepare([](int current, int total) {
			std::cerr << "Gathering information... " << current << "/" << total << "\r";
		});

		std::cerr << "Gathering information... Done!" << std::endl;

		projects = db.Query(detectors);
	}

	projects = projects.SortByName();

	// Display
	int num = 1;
	for (const auto& project : projects) {
		std::cout << num << ". " << project->name << std::endl;
		std::cout << "\t" << project->comment << std::endl;
		std::cout << "\t" << project->url << std::endl;
		std::cout << std::endl;
		num++;
	}

	if (projects.empty())
		std::cerr << "No projects found, sorry :(" << std::endl;

	return 0;
} catch (std::exception& e) {
	std::cerr << "Fatal error: " << e.what() << std::endl;
	return 1;
}
