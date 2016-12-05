#ifndef OPTIONS_H
#define OPTIONS_H

#define DEFAULT_CONF "raptohr.conf"

#include <string>
#include <iostream>

class Options {
public:
	Options() : conf(DEFAULT_CONF) { }
	std::string conf;
	
	bool validate() const;

	friend std::ostream& operator<<(std::ostream& out, const Options& o);
};

#endif