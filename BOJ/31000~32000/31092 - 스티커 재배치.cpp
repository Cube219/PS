#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    struct Sticker
    {
        char ch;
        int detach;
        int price;
    };
    vector<Sticker> d(m);
    for (auto& v : d) cin >> v.ch >> v.detach >> v.price;
    vector<int> src(n);
    for (auto& v : src) {
        cin >> v;
        v--;
    }
    string sub;
    cin >> sub;
    int subNum = sub.size();

    vector<int> minPrice(26, INF);
    int mmPrice = INF;
    for (auto& v : d) {
        int idx = v.ch - 'a';
        minPrice[idx] = min(minPrice[idx], v.price);
        mmPrice = min(mmPrice, minPrice[idx]);
    }

    int res = INF;
    for (int st = 0; st < n; ++st) {
        if (st + subNum > n) break;

        vector<int> req(26, 0);
        vector<vector<int>> minDetach(26);
        int curRes = 0;
        int detachNum = 0;
        for (int i = 0; i < subNum; ++i) {
            int idx = src[st + i];
            char srcCh = d[idx].ch;
            if (srcCh != sub[i]) {
                minDetach[srcCh - 'a'].push_back(0);
                req[sub[i] - 'a']++;
                detachNum++;
                curRes += d[idx].detach;
            }
        }

        for (int i = 0; i < 26; ++i) {
            while (req[i] > 0 && minDetach[i].size() > 0) {
                minDetach[i].pop_back();
                req[i]--;
                detachNum--;
            }
        }

        for (int i = 0; i < st; ++i) {
            int idx = src[i];
            minDetach[d[idx].ch - 'a'].push_back(d[idx].detach);
        }
        for (int i = st + subNum; i < n; ++i) {
            int idx = src[i];
            minDetach[d[idx].ch - 'a'].push_back(d[idx].detach);
        }
        int tmp = 0;
        for (int i = 0; i < 26; ++i) {
            sort(minDetach[i].begin(), minDetach[i].end(), [](const int& l, const int& r) {
                return l > r;
            });
            while (req[i] > 0) {
                if (minDetach[i].size() == 0 || minDetach[i].back() + tmp >= minPrice[i]) {
                    if (minPrice[i] == INF) {
                        curRes = INF;
                        goto end;
                    }
                    curRes += minPrice[i];
                } else {
                    curRes += minDetach[i].back() + tmp;
                    minDetach[i].pop_back();
                    detachNum--;
                    if (detachNum <= 0) tmp = mmPrice;
                }
                req[i]--;
            }
        }
    end:
        res = min(res, curRes);
    }

    if (res == INF) res = -1;
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
