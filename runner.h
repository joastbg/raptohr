#ifndef RUNNER_H
#define RUNNER_H


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <regex>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <experimental/random>
#include <bitset>
#include <type_traits>

#include "sha1.h"

#include "options.h"
#include "complex.h"
#include "matrix.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_EVENTS 10
#define PORT 6009

class DBTriple {
public:
	DBTriple(const std::string& s, const std::string& p, const std::string& o) : _s(s), _p(p), _o(o) { }
        
    const std::string spo() const { return std::string("spo:" + _s + ":" + _p + ":" + _o); }
    const std::string sop() const { return std::string("sop:" + _s + ":" + _o + ":" + _p); }
    const std::string ops() const { return std::string("ops:" + _o + ":" + _p + ":" + _s); }
    const std::string osp() const { return std::string("osp:" + _o + ":" + _s + ":" + _p); }
    const std::string pso() const { return std::string("pso:" + _p + ":" + _s + ":" + _o); } 
    const std::string pos() const { return std::string("pos:" + _p + ":" + _o + ":" + _s); }
    
    friend std::ostream& operator<<(std::ostream& out, const DBTriple& o);
    
private:
    std::string _s;
    std::string _p;
    std::string _o;
};

class Runner {
public:
	Runner(Options options) : options(options) {}
	void run();
private:
	const Options& options;
    struct sockaddr_in serv;
    struct sockaddr_in addr;
};

#endif