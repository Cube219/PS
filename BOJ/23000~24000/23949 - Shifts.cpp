#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, h;
    cin >> n >> h;
    vector<int> a(n), b(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    int sz1 = n, sz2 = 0;
    ll p1 = 1, p2 = 1;
    for(int i = 0; i < n; ++i) p1 *= 3;
    while(1) {
        if(p1 + p2 < p1 / 3 + p2 * 9) break;
        sz1--; sz2++;
        p1 /= 3; p2 *= 9;
    }

    vector<ll> aa, bb;
    vector<pair<ll, ll>> ab;
    auto bt2 = [&](auto&& self, int idx, ll cura, ll curb) -> void {
        if(idx == sz2) {
            ab.push_back({ cura, curb });
            aa.push_back(cura);
            bb.push_back(curb);
            return;
        }
        self(self, idx + 1, cura + a[n - 1 - idx], curb);
        self(self, idx + 1, cura, curb + b[n - 1 - idx]);
        self(self, idx + 1, cura + a[n - 1 - idx], curb + b[n - 1 - idx]);
    };
    bt2(bt2, 0, 0, 0);

    sort(aa.begin(), aa.end());
    aa.erase(unique(aa.begin(), aa.end()), aa.end());
    auto geta = [&](ll v) { return lower_bound(aa.begin(), aa.end(), v) - aa.begin(); };
    sort(bb.begin(), bb.end());
    bb.erase(unique(bb.begin(), bb.end()), bb.end());
    auto getb = [&](ll v) { return lower_bound(bb.begin(), bb.end(), v) - bb.begin(); };

    vector<vector<int>> sum(aa.size(), vector<int>(bb.size(), 0));
    for(auto [a, b] : ab) {
        sum[geta(a)][getb(b)]++;
    }
    for(int i = aa.size() - 1; i >= 0; --i) {
        for(int j = (int)bb.size() - 2; j >= 0; --j) {
            sum[i][j] += sum[i][j + 1];
        }
    }
    for(int j = bb.size() - 1; j >= 0; --j) {
        for(int i = (int)aa.size() - 2; i >= 0; --i) {
            sum[i][j] += sum[i + 1][j];
        }
    }

    ll res = 0;
    auto bt = [&](auto&& self, int idx, ll cura, ll curb) -> void {
        if(idx == sz1) {
            auto av = geta((ll)h - cura);
            auto bv = getb((ll)h - curb);
            if(av < aa.size() && bv < bb.size()) res += sum[av][bv];
            return;
        }
        self(self, idx + 1, cura + a[idx], curb);
        self(self, idx + 1, cura, curb + b[idx]);
        self(self, idx + 1, cura + a[idx], curb + b[idx]);
    };
    bt(bt, 0, 0, 0);

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
