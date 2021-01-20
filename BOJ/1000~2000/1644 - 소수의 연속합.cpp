#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> primes;
bool np[4000001];

void init()
{
    for(ll i = 2; i <= n; i++) {
        if(np[i] == false) primes.push_back(i);
        for(ll j = i * 2; j <= n; j += i) {
            np[j] = true;
        }
    }
}

ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    init();

    int st = 0;
    int ed = 0;
    ll sum = 0;
    while(1) {
        if(sum >= n) {
            sum -= primes[st];
            st++;
        } else {
            if(ed == primes.size()) break;
            sum += primes[ed];
            ed++;
        }
        if(sum == n) res++;
    }

    cout << res;

    return 0;
}
