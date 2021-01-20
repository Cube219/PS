#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int n, a[300001];
 
constexpr ll MOD = 998244353;
ll res;
 
ll divmod(ll a, ll b, ll mod)
{
    ll res = 1;
    ll ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n;
    for(int i = 0; i < n * 2; i++) {
        cin >> a[i];
    }
    sort(a, a + n*2);
 
    ll cnt = 1;
    
    for(int i = 1; i <= n; i++) {
        ll lhs = (n*2 - i + 1);
        cnt = (cnt * lhs) % MOD;
        cnt = divmod(cnt, i, MOD);
    }
 
    ll bSum = 0;
    for(int i = 0; i < n; i++) {
        int diff = a[n + i] - a[i];
        bSum += diff;
        bSum = bSum % MOD;
    }
    bSum = bSum * cnt;
    bSum = bSum % MOD;
 
    cout << bSum;
 
    return 0;
}
