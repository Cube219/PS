#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

constexpr int NSQRT = 4000;
bool isPrime[NSQRT];
vector<int> primes;
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i < NSQRT; i++) {
        for(int j = i * 2; j < NSQRT; j += i) {
            isPrime[j] = true;
        }
    }
    for(int i = 2; i < NSQRT; i++) {
        if(isPrime[i] == false) {
            primes.push_back(i);
        }
    }
}
void get_f_primes(int v)
{
    fPrimes.clear();

    for(int i = 0; i < primes.size(); i++) {
        if(v % primes[i] == 0) {
            if(fPrimes.size() == 0 || fPrimes.back().first != primes[i]) {
                fPrimes.push_back(make_pair(primes[i], 0));
            }
            fPrimes.back().second++;
            v /= primes[i];
            i--;
        }
    }
    if(v > 1) {
        fPrimes.push_back(make_pair(v, 1));
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    init_primes();
    get_f_primes(n);

    for(int i = 0; i < fPrimes.size(); i++) {
        for(int j = 0; j < fPrimes[i].second; j++) {
            cout << fPrimes[i].first << "\n";
        }
    }

    return 0;
}
