#include "runner.h"

void Runner::run() {

	std::cout << std::endl << ANSI_COLOR_GREEN << ">> booting up...";
        std::cout << ANSI_COLOR_RESET << std::endl;

	// Check options
	if (!options.validate()) return;
        //std::cout << options << std::endl;	
}