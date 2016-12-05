#include "runner.h"
#include "options.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define RAPTOHR_VERSION "0.02"

void usage() {
	std::cout << "usage: raptohr [--conf filename]" << std::endl;
}

void banner() {

	std::cout << std::endl << ANSI_COLOR_YELLOW << "Raptohr" << " ";
        std::cout << RAPTOHR_VERSION << ANSI_COLOR_RESET << std::endl;
	std::cout << "Copyright Gautr Systems AB" << std::endl;	
}

int main (int argc, char *argv[]) {

	Options options;
	if (argc == 1) usage();	
	for (int i = 1; i < argc; ++i) {
		if (!strncmp(argv[i], "--conf", 6))
            options.conf = argv[++i];		
	}

	banner();

	// Booting Raptohr
	Runner runner(options);
	runner.run();
	
	return 0;	
}