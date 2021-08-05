#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 9973;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/BerlekampMassey.h
// usage: ({0, 1, 1, 3, 5, 11}) // {1, 2}
template <ll mod = 998244353>
struct BerlekampMassey
{
    ll modpow(ll b, ll e)
    {
        ll ans = 1;
        for(; e; b = b * b % mod, e /= 2) if(e & 1) ans = ans * b % mod;
        return ans;
    }

    vector<ll> get(vector<ll> s)
    {
        int n = s.size(), L = 0, m = 0;
        vector<ll> C(n), B(n), T;
        C[0] = B[0] = 1;

        ll b = 1;
        for(int i = 0; i < n; ++i) {
            ++m;
            ll d = s[i] % mod;
            for(int j = 1; j < L + 1; ++j) {
                d = (d + C[j] * s[i - j]) % mod;
            }
            if(!d) continue;
            T = C;
            ll coef = d * modpow(b, mod - 2) % mod;
            for(int j = m; j < n; ++j) {
                C[j] = (C[j] - coef * B[j - m]) % mod;
            }
            if(2 * L > i) continue;
            L = i + 1 - L;
            B = T;
            b = d;
            m = 0;
        }

        C.resize(L + 1);
        C.erase(C.begin());
        for(ll& x : C) x = (mod - x) % mod;
        return C;
    }
};

// https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
// ex: a_i = a_i-1 + 2a_i-2 / a0 = 3, a1 = 4
//     -> get_nth({ 1, 2 }, { 3, 4 }, n);
template <ll mod = 998244353>
struct Kitamasa
{
    int get_nth(vector<ll> rec, vector<ll> dp, ll n)
    {
        int m = rec.size();
        vector<ll> s(m), t(m);
        s[0] = 1;
        if(m != 1) t[1] = 1;
        else t[0] = rec[0];
        auto mul = [&rec](const vector<ll>& v, const vector<ll>& w) {
            int m = v.size();
            vector<ll> t(2 * m);
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < m; k++) {
                    t[j + k] += 1ll * v[j] * w[k] % mod;
                    if(t[j + k] >= mod) t[j + k] -= mod;
                }
            }
            for(int j = 2 * m - 1; j >= m; j--) {
                for(int k = 1; k <= m; k++) {
                    t[j - k] += 1ll * t[j] * rec[k - 1] % mod;
                    if(t[j - k] >= mod) t[j - k] -= mod;
                }
            }
            t.resize(m);
            return t;
        };
        while(n) {
            if(n & 1) s = mul(s, t);
            t = mul(t, t);
            n >>= 1;
        }
        ll ret = 0;
        for(int i = 0; i < m; i++) ret += 1ll * s[i] * dp[i] % mod;
        return ret % mod;
    }
};

int tNum;
int n, m;
ll t;
vector<int> g[11], g2[201];
ll dp[301][201];
BerlekampMassey<MOD> bm;
Kitamasa<MOD> ki;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m >> t;
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int v = i * 10 + j;

                for(int inxt : g[i]) {
                    for(int jnxt : g[j]) {
                        int v2 = inxt * 10 + jnxt;
                        g2[v].push_back(v2);
                    }
                }
            }
        }

        vector<ll> v;
        dp[0][n - 1] = 1;
        for(int cnt = 1; cnt <= 300; ++cnt) {
            for(int i = 0; i < n * 10 + n; ++i) {
                dp[cnt][i] = 0;
            }
            for(int i = 0; i < n * 10 + n; ++i) {
                if((i / 10) == (i % 10)) continue;
                for(int nxt : g2[i]) {
                    dp[cnt][nxt] += dp[cnt - 1][i];
                    dp[cnt][nxt] %= MOD;
                }
            }

            ll vv = 0;
            for(int i = 0; i < n; ++i) {
                int idx = i * 10 + i;
                vv += dp[cnt][idx];
                vv %= MOD;
            }
            v.push_back(vv);
        }
        auto c = bm.get(v);
        ll res = 0;
        if(c.size() > 0) {
            res = ki.get_nth(c, v, t - 1);
        }
        cout << res << "\n";

        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for(int i = 0; i < n * 10 + n; ++i) {
            g2[i].clear();
        }
        dp[0][n - 1] = 0;
    }

    return 0;
}
