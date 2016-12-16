#ifndef MISC_H
#define MISC_H

#include <bitset>
#include <iostream>
#include <string>
#include <assert.h>
 
uint32_t gray_encode(uint32_t b);
uint32_t gray_decode(uint32_t g);
std::string to_binary(int value);
int test_gray();

#endif
