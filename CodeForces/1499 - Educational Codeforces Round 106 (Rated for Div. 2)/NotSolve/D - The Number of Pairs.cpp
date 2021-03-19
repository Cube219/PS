#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
ll c, d, x;
 
vector<pair<int, int>> fPrimes;
 
void get_f_primes(ll v)
{
    fPrimes.clear();
 
    if(v % 2 == 0) {
        int cnt = 0;
        while(v % 2 == 0) {
            cnt++;
            v /= 2;
        }
        fPrimes.push_back({ 2, cnt });
    }
    for(int i = 3; i * i <= v; i += 2) {
        if(v % i == 0) {
            int cnt = 0;
            while(v % i == 0) {
                cnt++;
                v /= i;
            }
            fPrimes.push_back({ i, cnt });
        }
    }
    if(v > 1) {
        fPrimes.push_back({ v, 1 });
    }
}
 
ll process(ll factor)
{
    ll cn = factor + d;
    if(cn % c != 0) return 0;
 
    ll n = cn / c;
 
    ll g = x / (c * n - d);
    ll l = (d * g + x) / c;
    ll t = l / g;
 
    get_f_primes(t);
 
    ll ret = 1;
    for(int i = 0; i < fPrimes.size(); ++i) {
        ret *= 2;
    }
    return ret;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> c >> d >> x;
        ll res = 0;
 
        for(ll i = 1; i*i <= x; ++i) {
            if(x % i != 0) continue;
 
            ll f = i;
            res += process(f);
            if(f != x / f) {
                res += process(x / f);
            }
        }
        cout << res << "\n";
    }
 
    return 0;
}
