#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    string str;
    cin >> str;
    int n = str.size();

    unordered_map<ll, vector<int>> pos;
    auto add = [&](ll hs, int p) {
        auto it = pos.find(hs);
        if(it == pos.end()) it = pos.insert({ hs, {} }).first;
        it->second.push_back(p);
    };
    for(int sz = 1; sz <= 4; ++sz) {
        if(sz > n) break;

        ll cur = 0, mx = 1;
        for(int i = 0; i < sz; ++i) {
            cur *= 27;
            mx *= 27;
            cur += str[i] - 'a' + 1;
        }
        add(cur, 0);
        for(int i = sz; i < n; ++i) {
            cur *= 27;
            cur -= (str[i - sz] - 'a' + 1) * mx;


            cur += str[i] - 'a' + 1;

            add(cur, i - sz + 1);
        }
    }

    unordered_map<ll, int> mem;
    ll mx = 1;
    for(int i = 0; i < 4; ++i) mx *= 27;

    auto geths = [](const string& str) {
        ll res = 0;
        for(char ch : str) {
            res *= 27;
            res += ch - 'a' + 1;
        }
        return res;
    };
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int n1 = s1.size(), n2 = s2.size();

        ll hs1 = geths(s1);
        ll hs2 = geths(s2);
        if(hs1 > hs2) {
            swap(hs1, hs2);
            swap(n1, n2);
        }

        ll hs = hs1 * mx + hs2;
        auto memit = mem.find(hs);
        if(memit != mem.end()) {
            cout << memit->second << "\n";
            continue;
        }

        auto it1 = pos.find(hs1);
        auto it2 = pos.find(hs2);
        if(it1 == pos.end() || it2 == pos.end()) {
            cout << "-1\n";
            continue;
        }

        auto& pos1 = it1->second;
        auto& pos2 = it2->second;
        int i1 = 0, i2 = 0;
        int res = INF;
        while(i1 < pos1.size() && i2 < pos2.size()) {
            int l = min(pos1[i1], pos2[i2]);
            int r = max(pos1[i1] + n1, pos2[i2] + n2);
            res = min(res, r - l);
            if(pos1[i1] + n1 < pos2[i2] + n2) i1++;
            else i2++;
        }

        cout << res << "\n";
        mem.insert({ hs, res });
    }
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
