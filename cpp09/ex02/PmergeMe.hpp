#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>
#include <ctime>

typedef std::pair<uint, uint> pair_t;
typedef std::vector<pair_t > vect_pair_t;
typedef std::deque<pair_t > deque_pair_t;


struct CompareFirst {
    bool operator()(const pair_t& element, uint val) const {
        return element.first < val;
    }
};

/// parse the args
void parser(std::vector<uint> &v, char **av, int ac);
// void listDeque(std::deque<uint> &d, std::vector<uint> &v);

void createPair(deque_pair_t &list_pair, std::deque<uint> &list);
void createPair(vect_pair_t &list_pair, std::vector<uint> &list);
// algorithm
void mergeInsert(std::vector<uint> &v);
void print(std::vector<uint> &v);
void mergeInsert(std::deque<uint> &v);
void print(std::deque<uint> &v);
