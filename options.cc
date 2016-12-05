#include "options.h"

bool Options::validate() const {
	
	// Check arguments here...
	
	return true;	
}

std::ostream& operator<<(std::ostream& out, const Options& o) {
	out << std::boolalpha;
	out << "-- Options" << std::endl;
	out << "options.conf:\t" << o.conf << std::endl;	
	return out;
}