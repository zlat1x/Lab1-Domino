#include "domino_dealer.h"
#include <stdexcept>
#include <limits>

namespace lab1::domino {
    long long domino_dealer::triangle_count(long long x) {
        if (x < 0) return 0;

        unsigned long long f1 = static_cast<unsigned long long>(x) + 1ull;
        unsigned long long f2 = static_cast<unsigned long long>(x) + 2ull;
        if ((f1 & 1ull) == 0ull) f1 >>= 1; else f2 >>= 1;

        const unsigned long long U = std::numeric_limits<unsigned long long>::max();
        if (f1 != 0ull && f2 > U / f1) 
            throw std::overflow_error("total_tiles overflows 64-bit");

        unsigned long long prod = f1 * f2;
        if (prod > static_cast<unsigned long long>(std::numeric_limits<long long>::max()))
            throw std::overflow_error("total_tiles overflows long long");

        return static_cast<long long>(prod);
    }

    unsigned long long domino_dealer::tri_ull(long long x) {
        if (x < 0) return 0ull;

        unsigned long long f1 = static_cast<unsigned long long>(x) + 1ull;
        unsigned long long f2 = static_cast<unsigned long long>(x) + 2ull;
        if ((f1 & 1ull) == 0ull) f1 >>= 1; else f2 >>= 1;

        return f1 * f2;
    }

    // Binary search for minimal j with tri_ull(j) > k
    long long domino_dealer::find_j_for_index(long long n, long long k) {
        unsigned long long kk = static_cast<unsigned long long>(k);

        long long lo = 0, hi = n;
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            unsigned long long t = tri_ull(mid);
            if (t > kk) 
                hi = mid; 
            else lo = mid + 1;
        }

        return lo;
    }

    domino_dealer::domino_dealer(long long n, unsigned long long seed) : n_(n) {
        if (n < 0) 
            throw std::invalid_argument("n must be >= 0");

        total_tiles_ = triangle_count(n);

        if (seed == 0) {
            std::random_device rd;
            std::seed_seq seq{ rd(), rd(), rd(), rd() };
            rng_ = std::mt19937_64(seq);
        } else {
            rng_.seed(seed);
        }
        
        reset();
    }

    void domino_dealer::reset() {
        remaining_ = total_tiles_;
        perm_.clear();
    }

    domino_tile domino_dealer::operator()() {
        if (remaining_ <= 0) 
            throw std::out_of_range("no tiles left");

        std::uniform_int_distribution<long long> dist(0, remaining_ - 1);
        long long r = dist(rng_);
        long long last = remaining_ - 1;

        long long val_r = r;
        auto it_r = perm_.find(r);
        if (it_r != perm_.end()) 
            val_r = it_r->second;

        long long val_last = last;
        auto it_last = perm_.find(last);
        if (it_last != perm_.end()) 
            val_last = it_last->second;

        perm_[r] = val_last;
        if (it_last != perm_.end()) 
            perm_.erase(it_last);

        --remaining_;

        const long long idx = val_r;
        const long long j = find_j_for_index(n_, idx);
        const unsigned long long base = tri_ull(j - 1);
        const long long i = idx - static_cast<long long>(base);

        return domino_tile{ i, j };
    }
}