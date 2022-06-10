#include <ext/pb_ds/assoc_container.hpp>

struct splitmix64_hash
{
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    uint64_t operator()(uint64_t x) const
    {
        return splitmix64(x + 0x2425260000242526);
    }
};

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/HashMap.h
// For CodeForces, or other places where hacking might be a problem:
/*
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct random_hash
{ // To use most bits rather than just the lowest ones:
    const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
    ll operator()(ll x) const { return __builtin_bswap64((x ^ RANDOM) * C); }
};
*/

template <typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, splitmix64_hash>;

template <typename K>
using hash_set = hash_map<K, __gnu_pbds::null_type>;

// hash_map<int, int> table({}, {}, {}, {}, {1 << 16});
