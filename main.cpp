// Lab 1 — Task 6 (Domino Dealer)
// Build:
//   g++ -std=c++20 -O2 -Wall -Wextra -pedantic -o lab1 main.cpp domino_dealer.cpp simulation.cpp

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "domino_dealer.h"
#include "simulation.h"

using lab1::domino::domino_dealer;
using lab1::sim::simulate_one_deal;
using lab1::sim::compute_stats;
using lab1::sim::experiment_range;
using lab1::sim::VLL;
using lab1::sim::ratio_row;

static int wrong_input() {
    std::cout << "wrong input\n";
    return 1;
}

int main() {
    return 0;
}