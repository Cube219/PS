#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

template <ll h1 = 3137, ll m1 = 998244353, ll h2 = 53, ll m2 = 1000000007>
struct HashStr
{
    vector<ll> v1, pow1, v2, pow2;
    HashStr(const string& str)
    {
        int n = str.size();
        v1.resize(n); pow1.resize(n);
        v1[0] = str[0]; pow1[0] = 1;
        for(int i = 1; i < n; ++i) {
            v1[i] = (v1[i - 1] * h1 % m1 + str[i]) % m1;
            pow1[i] = pow1[i - 1] * h1 % m1;
        }

        v2.resize(n); pow2.resize(n);
        v2[0] = str[0]; pow2[0] = 1;
        for(int i = 1; i < n; ++i) {
            v2[i] = (v2[i - 1] * h2 % m2 + str[i]) % m2;
            pow2[i] = pow2[i - 1] * h2 % m2;
        }
    }

    // [l, r]
    ll get(int l, int r)
    {
        ll res1 = v1[r];
        if(l > 0) {
            ll sub = v1[l - 1] * pow1[r - l + 1] % m1;
            res1 = (res1 - sub + m1) % m1;
        }
        ll res2 = v2[r];
        if(l > 0) {
            ll sub = v2[l - 1] * pow2[r - l + 1] % m2;
            res2 = (res2 - sub + m2) % m2;
        }
        return res1 << 32 | res2;
    }
};

void solve()
{
    string a, b;
    cin >> a >> b;

    if(a.size() > b.size()) {
        cout << "0";
        return;
    }

    vector<int> num(26, 0);
    for(char ch : a) num[ch - 'a']++;

    vector<int> num2(26, 0);
    auto ck = [&]() {
        bool res = true;
        for(int i = 0; i < 26; ++i) {
            if(num[i] != num2[i]) res = false;
        }
        return res;
    };
    set<ll> has;
    HashStr hs(b);

    int n = a.size();
    for(int i = 0; i < n; ++i) num2[b[i] - 'a']++;
    if(ck()) has.insert(hs.get(0, n - 1));

    for(int i = n; i < b.size(); ++i) {
        num2[b[i - n] - 'a']--;
        num2[b[i] - 'a']++;
        if(ck()) {
            ll v = hs.get(i - n + 1, i);
            has.insert(v);
        }
    }

    cout << has.size();
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
