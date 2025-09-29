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
}