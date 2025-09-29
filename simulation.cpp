#include "simulation.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <limits>

namespace lab1::sim {

static bool can_place_left(const domino_tile& t, long long left)  { return t.a == left || t.b == left; }
static bool can_place_right(const domino_tile& t, long long right){ return t.a == right || t.b == right; }

static bool place(domino_tile t, long long& left, long long& right) {
    const bool L = can_place_left(t, left);
    const bool R = can_place_right(t, right);

    if (!L && !R) return false; 

    if (L && R) {
        const long long mn = std::min(t.a, t.b);
        if (left == mn) {
            left = (t.a == left ? t.b : t.a);
            return true;
        }
        right = (t.a == right ? t.b : t.a);
        return true;
    }

    if (L) {
        left = (t.a == left ? t.b : t.a);
        return true;
    }
    right = (t.a == right ? t.b : t.a);
    return true;
}

long long simulate_one_deal(domino_dealer& dealer) {
    dealer.reset();
    if (dealer.total_tiles() == 0) return 0;

    domino_tile first = dealer();
    long long left = first.a;
    long long right = first.b;
    long long placed = 1;

    while (dealer.remaining_tiles() > 0) {
        domino_tile next = dealer();
        if (!place(next, left, right)) break;
        ++placed;
    }
    return placed;
}

double mean(const VLL& xs) {
    if (xs.empty()) throw std::invalid_argument("mean of empty");
    long double s = 0;
    for (long long v : xs) s += static_cast<long double>(v);
    return static_cast<double>(s / xs.size());
}

double median(VLL xs) {
    if (xs.empty()) throw std::invalid_argument("median of empty");
    std::nth_element(xs.begin(), xs.begin() + xs.size()/2, xs.end());
    long long mid = xs[xs.size()/2];
    if (xs.size() % 2 == 1) return static_cast<double>(mid);
    auto it = std::max_element(xs.begin(), xs.begin() + xs.size()/2);
    long long mid2 = *it;
    return (static_cast<long double>(mid) + static_cast<long double>(mid2)) / 2.0L;
}

stats_result compute_stats(const VLL& sizes) {
    if (sizes.empty()) throw std::invalid_argument("sizes empty");
    std::vector<std::pair<long long,long long>> pairs;
    pairs.reserve(sizes.size());
    VLL sorted = sizes;
    std::sort(sorted.begin(), sorted.end());

    long long current = sorted[0];
    long long cnt = 1;

    for (std::size_t i = 1; i < sorted.size(); ++i) {
        if (sorted[i] == current) ++cnt;
        else { pairs.push_back({current, cnt}); current = sorted[i]; cnt = 1; }
    }

    pairs.push_back({current, cnt});

    long long best_size = pairs[0].first;
    long long best_cnt = pairs[0].second;
    for (const auto& p : pairs) {
        if (p.second > best_cnt || (p.second == best_cnt && p.first < best_size)) {
            best_cnt = p.second; best_size = p.first;
        }
    }

    stats_result r;
    r.hist_pairs = std::move(pairs);
    r.mode_size = best_size;
    r.mean_val = mean(sizes);
    r.median_val = median(sizes);
    return r;
}

std::vector<ratio_row> experiment_range(long long lo, long long hi,
                                        long long deals_per_n, unsigned long long base_seed) {
    if (hi < lo) std::swap(hi, lo);
    std::vector<ratio_row> rows;
    for (long long n = lo; n <= hi; ++n) {
        lab1::domino::domino_dealer dealer(n, base_seed + static_cast<unsigned long long>(n));
        VLL sizes;
        sizes.reserve(static_cast<std::size_t>(deals_per_n));
        for (long long d = 0; d < deals_per_n; ++d) sizes.push_back(simulate_one_deal(dealer));
        const long long T = dealer.total_tiles();
        const double m = mean(sizes);
        const double med = median(sizes);
        rows.push_back({ n, T, m / static_cast<double>(T), med / static_cast<double>(T) });
        if (n == std::numeric_limits<long long>::max()) break; 
    }
    return rows;
}

} 