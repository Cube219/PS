#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto& v : a) {
        cin >> v;
    }
    set<pair<int, int>> ban;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        ban.insert({ x, y });
    }

    sort(a.begin(), a.end());
    struct Node
    {
        int a, cnt;
    };
    vector<Node> d;
    for(int v : a) {
        if(d.size() == 0 || d.back().a != v) d.push_back({ v, 0 });
        d.back().cnt++;
    }

    vector<int> cnts;
    for(auto& v : d) {
        cnts.push_back(v.cnt);
    }
    sort(cnts.begin(), cnts.end());
    cnts.erase(unique(cnts.begin(), cnts.end()), cnts.end());
    vector<vector<int>> cntList(cnts.size());
    for(auto& v : d) {
        int idx = lower_bound(cnts.begin(), cnts.end(), v.cnt) - cnts.begin();
        cntList[idx].push_back(v.a);
    }

    ll res = 0;
    struct QNode
    {
        int v;
        int idx1, idx2;
        bool operator<(const QNode& rhs) const
        {
            return v < rhs.v;
        }
    };
    for(int i = 0; i < cntList.size(); ++i) {
        int c1 = cnts[i];
        auto& v1Vec = cntList[i];
        for(int j = i; j < cntList.size(); ++j) {
            int c2 = cnts[j];
            auto& v2Vec = cntList[j];
            priority_queue<QNode> pq;
            pq.push({ v1Vec.back() + v2Vec.back(), (int)v1Vec.size() - 1, (int)v2Vec.size() - 1 });
            set<pair<int, int>> idxSkip;
            idxSkip.insert({ (v1Vec.size() - 1), (v2Vec.size() - 1) });
            while(pq.empty() == false) {
                QNode cur = pq.top();
                pq.pop();
                int v1 = v1Vec[cur.idx1];
                int v2 = v2Vec[cur.idx2];
                if(v1 > v2) swap(v1, v2);
                if(v1 != v2 && ban.find({ v1, v2 }) == ban.end()) {
                    res = max(res, (ll)(v1 + v2) * (c1 + c2));
                    break;
                }

                if(cur.idx1 > 0 && idxSkip.find({ cur.idx1 - 1, cur.idx2 }) == idxSkip.end()) {
                    pq.push({ v1Vec[cur.idx1 - 1] + v2Vec[cur.idx2], cur.idx1 - 1, cur.idx2 });
                    idxSkip.insert({ cur.idx1 - 1, cur.idx2 });
                }
                if(cur.idx2 > 0 && idxSkip.find({ cur.idx1, cur.idx2 - 1 }) == idxSkip.end()) {
                    pq.push({ v1Vec[cur.idx1] + v2Vec[cur.idx2 - 1], cur.idx1, cur.idx2 - 1 });
                    idxSkip.insert({ cur.idx1, cur.idx2 - 1 });
                }
            }
        }
    }

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
        solve();
    }

    return 0;
}
