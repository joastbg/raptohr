// --------------------------------------------------------
// SIGNAL IMPL.
//
// Motivation: -
//
// Copyright 2016 Gautr Systems AB
// http://www.github.com/joastbg 
// --------------------------------------------------------

#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

template <typename T>
class Signal;

template <typename T>
std::ostream& operator<< (std::ostream&, Signal<T>&);

template <typename T>
class Signal {
public:	
    Signal() {  }
    T avg();
    
    const std::string str() { 
        std::stringstream ss;
        
        for (int i=0;i<v.size();i++) {
            ss << "{" << v[i].str() << "}";
            if (i < v.size() - 1) ss << ", ";
        }
            
        return ss.str();
    }
    
    void add(T& t) {
        v.push_back(t);
    }
    
    friend std::ostream& operator<< <>(std::ostream&, Signal<T>&);
private:
    std::vector<T> v;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Signal<T>& s) {	
	out << "-- Signal<T> :: [" << s.str() << "]" << std::endl;	
	return out;
}

#endif