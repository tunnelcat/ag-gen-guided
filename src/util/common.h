/** \file util.h
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date June 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 */

#ifndef UTIL_COMMON_H
#define UTIL_COMMON_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef DEBUG_BUILD
#define DEBUG(x)                                                               \
    do {                                                                       \
        std::cerr << x << endl;                                                \
    } while (0)
#else
#define DEBUG(x)
#endif

static char alphabet[35] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                            '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                            'i', 'j', 'k', 'l', 'm', 'o', 'p', 'q', 'r',
                            's', 't', 'u', 'v', 'w', 'x', 'u', 'z'};

// Number
unsigned int base_convert_string(std::string data, int base);
std::vector<int> base_convert_int(int num, int base);
std::vector<int> base_convert(std::string num, int from, int to);

std::vector<std::string> split(std::string str, char delim);
std::string trim(std::string str);

#endif // UTIL_COMMON_H
