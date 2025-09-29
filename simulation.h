#pragma once
#include "domino_dealer.h"
#include <vector>
#include <utility>

namespace lab1::sim {

using lab1::domino::domino_tile;
using lab1::domino::domino_dealer;

using VLL = std::vector<long long>;

long long simulate_one_deal(domino_dealer& dealer);

double mean(const VLL& xs);

double median(VLL xs);

struct stats_result {
    std::vector<std::pair<long long,long long>> hist_pairs; 
    long long mode_size; 
    double mean_val;
    double median_val;
};

stats_result compute_stats(const VLL& sizes);

struct ratio_row {
    long long n;
    long long total_tiles;
    double mean_ratio;
    double median_ratio;
};

std::vector<ratio_row> experiment_range(long long lo, long long hi,
                                        long long deals_per_n, unsigned long long base_seed);

}