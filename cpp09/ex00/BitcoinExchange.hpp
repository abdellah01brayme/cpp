#pragma once
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <limits>
#include <iomanip>

#define DELIMITER_DATE '-'

void readSrc(std::map<std::string, double> &data, const std::string &fileName);
void btc(std::map<std::string, double> &data, const char *file_name);


