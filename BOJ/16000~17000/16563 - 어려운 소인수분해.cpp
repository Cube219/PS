#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

constexpr int MAXN = 5000000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }
}
void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d", &n);

    init_primes();
    
    for(int i = 0; i < n; i++) {
        // cout << i << "\n";
        scanf("%d", &k);
        get_f_primes(k);

        for(int j = 0; j < fPrimes.size(); j++) {
            for(int j2 = 0; j2 < fPrimes[j].second; j2++) {
                printf("%d ", fPrimes[j].first);
            }
        }
        printf("\n");
    }

    return 0;
}
