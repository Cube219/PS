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
    cnt -= 2;
    ll tmp = 1, tmp2 = 1;
    for(int i = 0; i < cnt - 1; ++i) {
        tmp2 = tmp2 * 2;
        tmp2 = tmp2 % MOD;
    }
    tmp = tmp2 * 2;
    tmp = tmp % MOD;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m - 1; ++j) {
            if(map[i][j] == 'o' && map[i][j+1] == 'o') {
                if(j > 0 && map[i][j - 1] == 'o') {
                    if(j < m - 2 && map[i][j+2] == 'o') {
                        res += (tmp - 1);
                    } else {
                        res += (tmp - 1);
                    }
                } else {
                    res += tmp;
                }
                res = res % MOD;
            }
        }
    }

    for(int j = 0; j < m; ++j) {
        for(int i = 0; i < n - 1; ++i) {
            if(map[i][j] == 'o' && map[i+1][j] == 'o') {
                if(i > 0 && map[i-1][j] == 'o') {
                    if(i < n - 2 && map[i + 2][j] == 'o') {
                        res += (tmp2 - 1);
                    } else {
                        res += (tmp2 - 1);
                    }
                } else {
                    res += tmp;
                }
                res = res % MOD;
            }
        }
    }

    cout << res;

    return 0;
}
