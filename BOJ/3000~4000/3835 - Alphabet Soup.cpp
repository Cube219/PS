#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

using ll = long long int;
constexpr ll MOD = 100000007;

struct KMP
{
    vector<int> fail;
    void init_fail(const vector<int>& w)
    {
        int wn = w.size();
        fail.clear();
        fail.resize(wn, 0);

        int j = 0;
        for(int i = 1; i < wn; ++i) {
            while(j > 0 && w[i] != w[j]) {
                j = fail[j - 1];
            }
            if(w[i] == w[j]) {
                fail[i] = j + 1;
                j++;
            }
        }
    }
    void get(const vector<int>& s, const vector<int>& w, vector<int>& res)
    {
        init_fail(w);
        res.clear();

        int sn = s.size();
        int wn = w.size();

        int j = 0;
        for(int i = 0; i < sn; ++i) {
            while(j > 0 && s[i] != w[j]) {
                j = fail[j - 1];
            }
            if(s[i] == w[j]) {
                if(j == wn - 1) {
                    res.push_back(i - wn + 1);
                    j = fail[j];
                } else {
                    j++;
                }
            }
        }
    }
};

int n, k;
int d[360001];
vector<int> g1, g2;
KMP kmp;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if(b % 2 == 1) {
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}

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

    while(1) {
        cin >> k >> n;
        if(n == -1) break;

        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        g1.resize(n);
        g2.resize(n * 2 - 1);
        for(int i = 0; i < n - 1; ++i) {
            g1[i] = d[i + 1] - d[i];
            g2[i] = g1[i];
            g2[i + n] = g1[i];
        }
        g1[n - 1] = d[0] + 360000 - d[n - 1];
        g2[n - 1] = g1[n - 1];

        vector<int> knum;
        kmp.get(g2, g1, knum);
        int gap = n / knum.size();

        ll res = 0;
        for(int i = 0; i < n; i += gap) {
            res += pw(k, gcd(n, i));
            res %= MOD;
        }
        res = divmod(res, knum.size(), MOD);

        cout << res << "\n";
    }

    return 0;
}
