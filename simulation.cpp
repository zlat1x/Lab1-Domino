#include "simulation.h"
#include <algorithm>
#include <numeric>

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