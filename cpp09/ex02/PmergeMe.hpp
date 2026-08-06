#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>

bool checkArg(char *s);
void parser(std::vector<uint> &v, char **av, int ac);


void mergeInsert(std::vector<uint> &v);