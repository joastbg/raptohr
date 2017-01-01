// --------------------------------------------------------
// SPARSE MATRIX IMPL.
//
// Motivation: Portability and efficiency
//
// Copyright 2016 Gautr Systems AB
// http://www.github.com/joastbg 
// --------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <type_traits>

template <class int_type>
class Hash {
public:
    size_t operator()(const std::pair<int_type,int_type> &p) const {
        return p.first + 71437 * p.second; 
    }
};

template <typename T>
class Matrix;

enum AllowedTypes { ROW_MAJOR, COLUMN_MAJOR };

template <typename T>
struct MatrixRow;

template <typename T>
struct MatrixCol;

template <typename T>
std::ostream& operator<< (std::ostream&, Matrix<T>&);

template <typename T>
class Matrix {
public:

    static constexpr unsigned short rows = 1024;
    static constexpr unsigned short cols = 1024;

	Matrix() {}
   
    friend std::ostream& operator<< <>(std::ostream&, Matrix<T>&);
    friend struct MatrixRow<T>;
    friend struct MatrixCol<T>;
    
    // arithmetic operators        
	inline Matrix operator+(const Matrix& b) const { return Matrix(); }
	inline Matrix operator-(const Matrix& b) const { return Matrix(); }
    
    // getters & setters 
    //T operator [](int i) const { return registers[i]; }
    //T& operator [](int i) { return registers[i]; }
    MatrixRow<T> operator[](unsigned int column) { return MatrixRow<T>(*this, column);}
     
    // printers & helpers
    
    const std::string str() { 
        std::stringstream ss;
        
        ss << "[TODO]";
        
        return ss.str();
    }
        
    void debug(std::ostream& out) { 
    
        out << "-- Matrix :: debug:" << std::endl;
        for (auto it = repr.begin(); it != repr.end(); ++it) {
            out << " [" << it->first << "] = " << it->second << ";";
        }        
        out << std::endl;
        
        out << " trace = " << this->trace() << std::endl; 
    }
        
    // misc properties
	inline T trace() const { 
        T t{};
        return t;
    }
    
    inline double det() const { return 0; }
    inline double rank() const { return 0; }
        
private:

    T& get(int col, int row) { return repr[hash(col, row)]; }
    
    std::string hash(int col, int row) { 
        std::stringstream ss;        
        ss << col;
        ss << ":";
        ss << row;
        return ss.str();
    }
    
    std::unordered_map<std::string, T> repr;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Matrix<T>& m) {	
	out << "-- Matrix :: " << m.str() << std::endl;	
	return out;
}

template <typename T>
struct MatrixRow {
    Matrix<T>& own;
    unsigned int r;
    MatrixRow(Matrix<T>& owner, unsigned int row) : own(owner), r(row) {}
    T& operator[](unsigned int col) const { 
        return own.get(col, r);
    }
};

template <typename T>
struct MatrixCol {
    Matrix<T>& own;
    unsigned int c;    
    MatrixCol(Matrix<T>& owner, unsigned int col) : own(owner), c(col) {}
    T& operator[](unsigned int row) const { 
        return own.get(c, row);
    }
};

#endif