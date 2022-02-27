#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k, c;
    cin >> n >> k >> c;
    vector<vector<int>> s(n, vector<int>(k));
    for(auto& v1 : s) for(auto& v2 : v1) cin >> v2;

    struct Node
    {
        int score;
        int forceNum;
        vector<int> selectIdx;
        vector<char> fixed;
        bool operator<(const Node& rhs) const
        {
            return score < rhs.score;
        }
    };

    auto getSelectIdx = [&](int forceNum, vector<int> selectIdx, vector<char> fixedIdx) {
        vector<int> res = { selectIdx.begin(), selectIdx.begin() + forceNum };
        for(int i = forceNum; i < k; ++i) {
            int mx = -1, mxIdx = -1;
            for(int j = 0; j < n; ++j) {
                if(fixedIdx[j]) continue;
                if(mx < s[j][i]) {
                    mx = s[j][i];
                    mxIdx = j;
                }
            }

            if(mxIdx == -1) {
                res.clear();
                return res;
            }
            res.push_back(mxIdx);
            fixedIdx[mxIdx] = true;
        }
        return res;
    };
    auto getScore = [&](vector<int>& selectIdx) {
        int res = 0;
        for(int i = 0; i < k; ++i) {
            int mx = -1;
            for(int idx : selectIdx) {
                mx = max(mx, s[idx][i]);
            }
            res += mx;
        }
        return res;
    };

    auto initIdx = getSelectIdx(0, {}, vector<char>(n, false));
    int initScore = getScore(initIdx);
    priority_queue<Node> pq;
    pq.push({ initScore, 0, initIdx, vector<char>(n, false) });
    for(int zz = 1; zz < c; ++zz) {
        auto [_, forceNum, selectIdx, fixedIdx] = pq.top();
        pq.pop();

        for(int i = forceNum; i < k; ++i) {
            fixedIdx[selectIdx[i]] = true;
            auto newSelectIdx = getSelectIdx(forceNum, selectIdx, fixedIdx);
            if(newSelectIdx.size() > 0) {
                auto newScore = getScore(newSelectIdx);
                pq.push({ newScore, forceNum, newSelectIdx, fixedIdx });
            }
            forceNum++;
        }
    }

    cout << pq.top().score;
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
