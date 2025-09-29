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
    long long n = -1;
    long long deals = -1;
    unsigned long long seed = 0ULL;

    std::cout << "Enter maximum pip n (tiles have numbers 0..n): ";
    if (!(std::cin >> n) || n < 0) 
        return wrong_input();

    std::cout << "Enter number of deals to simulate: ";
    if (!(std::cin >> deals) || deals <= 0) 
        return wrong_input();

    std::cout << "Optional: enter RNG seed (0 to use non-deterministic seed): ";
    if (!(std::cin >> seed) || seed < 0) 
        return wrong_input();

    return 0;
}