#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <deque>
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
    vector<vector<char>> a(n, vector<char>(m));
    for (auto& v : a)
        for (auto& v2 : v) cin >> v2;

    // 0: 후보 / 1: 선택 / -1: 제거
    vector<int> s(m, 0);
    int selectNum = 0, candiNum = m;
    for (int i = 0; i < n; ++i) {
        auto& aa = a[i];

        if (selectNum + candiNum == m - k) break;

        vector<set<int>> idx(26);
        for (int j = m - 1; j >= 0; --j) {
            if (s[j] == 0) {
                idx[a[i][j] - 'a'].insert(j);
            }
        }

        int cur = 0;
        char curch = 0;
        vector<int> select;
        while (1) {
            int resIdx = INF;
            char resCh = 'z' + 1;
            for (int j = 0; j < 26; ++j) {
                auto it = idx[j].lower_bound(cur);
                if (it != idx[j].end()) {
                    resIdx = *it;
                    resCh = 'a' + j;
                    break;
                }
            }
            if (select.size() + selectNum >= m - k && curch != resCh) break;

            if (resIdx == INF) {
                s[select.back()] = 1;
                selectNum++;
                select.pop_back();

                cur = select.size() > 0 ? select.back() : 0;
                curch = 0;
                continue;
            }

            select.push_back(resIdx);
            cur = resIdx;
            curch = resCh;

            idx[curch - 'a'].erase(cur);
        }

        candiNum = 0;
        for (int j = 0; j < m; ++j) {
            if (s[j] == 0) s[j] = -1;
        }
        char lastCh = aa[select.back()];
        while (select.size() > 0 && aa[select.back()] == lastCh) {
            s[select.back()] = 0;
            candiNum++;
            select.pop_back();
        }
        for (int i : select) {
            s[i] = 1;
            selectNum++;
        }
    }

    for (int i = m - 1; i >= 0 && selectNum < m - k; --i) {
        if (s[i] == 0) {
            s[i] = 1;
            selectNum++;
        }
    }

    string res;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[j] == 1) res.push_back(a[i][j]);
        }
    }

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
