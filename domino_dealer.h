#pragma once
#include <vector>
#include <random>
#include <unordered_map>

namespace lab1::domino {

    struct domino_tile {
        long long a{};
        long long b{};
    };

    class domino_dealer {
        public:
        // seed = 0 -> random_device
        explicit domino_dealer(long long n, unsigned long long seed = 0);

        void reset();

        domino_tile operator()();

        long long total_tiles() const noexcept { return total_tiles_; } // T = (n+1)(n+2)/2
        long long remaining_tiles() const noexcept { return remaining_;}
        long long n() const noexcept { return n_; }

        private:
        static long long triangle_count(long long x);
        static unsigned long long tri_ull(long long x);
        static long long find_j_for_index(long long n, long long k);

        long long n_{};
        long long total_tiles_{};
        long long remaining_{};
        std::mt19937_64 rng_{};

        std::unordered_map<long long, long long> perm_;
    };
}