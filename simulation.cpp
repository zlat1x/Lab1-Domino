#include "simulation.h"
#include <algorithm>
#include <numeric>

namespace lab1::sim {

double mean(const std::vector<int>& xs) {
    if (xs.empty()) return 0.0;
    long long sum = 0; for (int v : xs) sum += v;
    return double(sum) / double(xs.size());
}

double median(std::vector<int> xs) {
    if (xs.empty()) return 0.0;
    std::sort(xs.begin(), xs.end());
    size_t m = xs.size() / 2;
    if (xs.size() % 2) return double(xs[m]);
    return 0.5 * (double(xs[m-1]) + double(xs[m]));
}

std::vector<long long> histogram(const std::vector<int>& sizes, long long T) {
    std::vector<long long> hist(static_cast<size_t>(T + 1), 0);
    for (int s : sizes) if (0 <= s && s <= T) ++hist[static_cast<size_t>(s)];
    return hist;
}

} 