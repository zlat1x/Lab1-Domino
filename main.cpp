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

    // Single-n stats
    {
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
    }

    std::cout << "\nRun experiment over n-range? (0 = No, 1 = Yes): ";
    int run_exp = 0;
    if (!(std::cin >> run_exp) || (run_exp != 0 && run_exp != 1)) 
        return wrong_input();

    if (run_exp == 1) {
        long long lo = 0, hi = 0;
        std::cout << "Enter n-range (inclusive) as: min max: ";
        if (!(std::cin >> lo >> hi) || lo < 0 || hi < 0) 
            return wrong_input();
        if (hi < lo) 
            std::swap(lo, hi);
        
        const auto rows = experiment_range(lo, hi, deals, seed);

        int w_n = 2, w_T = 5;
        for (const ratio_row& r : rows) {
            w_n = std::max(w_n, (int)std::to_string(r.n).size());
            w_T = std::max(w_T, (int)std::to_string(r.total_tiles).size());
        }
        std::cout << "\n " << std::setw(w_n) << "n"
                  << " | " << std::setw(w_T) << "total"
                  << " | mean/T | median/T\n";
        std::cout << std::string(2 + w_n + 3 + w_T + 13, '-') << "\n";

        std::cout << std::fixed << std::setprecision(6);
        for (const ratio_row& r : rows) {
            std::cout << " " << std::setw(w_n) << r.n << " | "
                      << std::setw(w_T) << r.total_tiles << " | "
                      << r.mean_ratio << " | " << r.median_ratio << "\n";
        }
    }

    return 0;
}