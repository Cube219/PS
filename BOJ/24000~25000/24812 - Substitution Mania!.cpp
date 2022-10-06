#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    string src, dst;
    getline(cin, src);
    getline(cin, dst);
    string ss, dd;
    vector<char> has(26, false);
    for(int i = 0; i < src.size(); ++i) {
        if(src[i] == ' ' || has[src[i] - 'a']) continue;
        ss.push_back(src[i]);
        dd.push_back(dst[i]);
        has[src[i] - 'a'] = true;
    }
    swap(ss, src);
    swap(dd, dst);

    int n;
    cin >> n;
    vector<string> d(n);
    for(auto& v : d) cin >> v;

    string target, res;
    getline(cin, target);
    getline(cin, target);

    int sz1 = n / 2;
    vector<int> use(n, 1);

    auto process = [&]() {
        vector<int> c1, c2;
        for(int i = 0; i < n; ++i) {
            if(use[i] == 1) c1.push_back(i);
            else c2.push_back(i);
        }

        map<string, vector<int>> mp;
        vector<int> table(26), nxt(26);
        do {
            iota(table.begin(), table.end(), 0);
            for(int idx : c1) {
                auto& cp = d[idx];
                for(int i = 0; i < 26; ++i) {
                    nxt[i] = cp[table[i]] - 'a';
                }
                swap(table, nxt);
            }
            string r1;
            for(char ch : src) {
                if(ch == ' ') r1.push_back(' ');
                else r1.push_back(table[ch - 'a'] + 'a');
            }
            mp.insert({ r1, table });
        } while(next_permutation(c1.begin(), c1.end()));

        do {
            iota(table.begin(), table.end(), 0);
            for(int idx : c2) {
                auto& cp = d[idx];
                for(int i = 0; i < 26; ++i) {
                    nxt[i] = cp[table[i]] - 'a';
                }
                swap(table, nxt);
            }
            for(int i = 0; i < 26; ++i) {
                nxt[table[i]] = i;
            }
            // swap(nxt, table);

            string r2;
            for(char ch : dst) {
                if(ch == ' ') r2.push_back(' ');
                else r2.push_back(nxt[ch - 'a'] + 'a');
            }

            auto it = mp.find(r2);
            if(it != mp.end()) {
                auto& t1 = it->second;
                for(int i = 0; i < 26; ++i) {
                    nxt[i] = table[t1[i]];
                }
                swap(table, nxt);
                for(int i = 0; i < 26; ++i) {
                    nxt[table[i]] = i;
                }

                for(char ch : target) {
                    if(ch == ' ') res.push_back(' ');
                    else res.push_back(nxt[ch - 'a'] + 'a');
                }
            }
        } while(res.size() == 0 && next_permutation(c2.begin(), c2.end()));
    };

    for(int i = 0; i < sz1; ++i) use[i] = 0;
    do {
        process();
    } while(res.size() == 0 && next_permutation(use.begin(), use.end()));

    cout << res;
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
