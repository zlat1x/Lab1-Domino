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

    domino_dealer dealer(n, seed);
    VLL sizes;
    sizes.reserve(static_cast<std::size_t>(deals));
    for (long long d = 0; d < deals; ++d) {
        sizes.push_back(simulate_one_deal(dealer));
    }

    const auto st = compute_stats(sizes);

    std::cout << "\nDistribution of deal sizes (tiles placed):\n";
    std::cout << std::fixed << std::setprecision(4);
    for (const auto& p : st.hist_pairs) {
        long long s = p.first;
        long long cnt = p.second;
        double pct = 100.0 * static_cast<double>(cnt) / static_cast<double>(deals);
        std::cout << "Size " << s << ": " << cnt << " deals, " << pct << "%\n";
    }

    std::cout << "\nMost frequent size: " << st.mode_size << "\n";
    std::cout << "Mean size:   " << st.mean_val << "\n";
    std::cout << "Median size: " << st.median_val << "\n";
    
    return 0;
}