#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 998244353;

int n, m;
char buf[300001];
vector<char> map[300001];
ll res;
ll cnt;
ll dp[300001];
ll n2[300001];

// (a / b) % mod == (a * b^(mod-2)) % mod
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
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        map[i].resize(m + 2);
        cin >> buf;
        for(int j = 0; j < m; ++j) {
            map[i][j] = buf[j];
            if(map[i][j] == 'o') cnt++;
        }
    }
    int nmmax = max(n, m);
    n2[0] = 1;
    for(int i = 1; i <= cnt; ++i) {
        n2[i] = (n2[i - 1] * 2) % MOD;
    }
    dp[2] = 1;
    dp[3] = 3;
    for(int i = 4; i <= nmmax; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2] + n2[i - 2] + dp[i - 2];
        dp[i] %= MOD;
    }

    bool conn;
    int num;
    for(int i = 0; i < n; ++i) {
        conn = false;
        num = 0;
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'o') {
                if(conn == false) {
                    conn = true;
                    num = 0;
                }
                num++;
            } else {
                if(conn == true) {
                    res += dp[num] * n2[cnt - num];
                    res %= MOD;
                    conn = false;
                }
            }
        }
        if(conn == true) {
            res += dp[num] * n2[cnt - num];
            res %= MOD;
        }
    }

    for(int j = 0; j < m; ++j) {
        conn = false;
        num = 0;
        for(int i = 0; i < n; ++i) {
            if(map[i][j] == 'o') {
                if(conn == false) {
                    conn = true;
                    num = 0;
                }
                num++;
            } else {
                if(conn == true) {
                    res += dp[num] * n2[cnt - num];
                    res %= MOD;
                    conn = false;
                }
            }
        }
        if(conn == true) {
            res += dp[num] * n2[cnt - num];
            res %= MOD;
        }
    }

    cout << res;

    return 0;
}
