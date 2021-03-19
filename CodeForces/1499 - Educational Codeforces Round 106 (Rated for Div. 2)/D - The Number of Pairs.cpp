#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int c, d, x;
 
constexpr int MAXN = 21000001;
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
 
 
int process(int factor)
{
    int cn = factor + d;
    if(cn % c != 0) return 0;
 
    int n = cn / c;
 
    int cnt = 0, last = 0;
    while(n > 1) {
        int f = min_factor[n];
        if(last != f) {
            last = f;
            cnt++;
        }
        n /= f;
    }
 
    int ret = (1 << cnt);
    return ret;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    init_primes();
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> c >> d >> x;
        int res = 0;
 
        for(int i = 1; i*i <= x; ++i) {
            if(x % i != 0) continue;
 
            int f = i;
            res += process(f);
            if(f != x / f) {
                res += process(x / f);
            }
        }
        cout << res << "\n";
    }
 
    return 0;
}
