#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
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
    int n, m, k;
    cin >> n >> m >> k;
    struct Node
    {
        struct QNode
        {
            ll v, subv;
            int sz;
            int idx;
            bool isFrontInsert;
            bool operator<(const QNode& rhs) const
            {
                return v > rhs.v;
            }
        };
        vector<int> c;
        int x, y;

        vector<ll> pre;
        vector<ll> kth;
        priority_queue<QNode> pq;

        void init()
        {
            sort(c.begin(), c.end());
            if(x == 0) {
                pq.push({ 0, 0, 0, -1, false });
            } else if(c.size() >= x) {
                pre.resize(x);
                pre[0] = c[0];
                for(int i = 1; i < x; ++i) {
                    pre[i] = c[i] + pre[i - 1];
                }
                pq.push({ pre[x - 1], 0, 0, x - 1, false });
            }
        }

        ll getKth(int k)
        {
            if(kth.size() > k) return kth[k];
            assert(kth.size() == k);

            if(pq.empty()) {
                kth.push_back(-1);
                return -1;
            }

            auto [v, subv, sz, idx, isFrontInsert] = pq.top();
            pq.pop();
            kth.push_back(v);

            // 앞에 하나 넣기
            if(sz > 0 && sz < y && x - sz >= 0) {
                int newSz = sz + 1;
                int newIdx = idx;
                ll newSubv = subv + c[x - newSz + 1];
                ll newV = newSubv;
                if(x - newSz - 1 >= 0) newV += pre[x - newSz - 1];
                pq.push({ newV, newSubv, newSz, newIdx, true });
            }

            // 뒤에 하나 지우고 다음 것 넣기
            if(sz > 0 && !isFrontInsert && idx < (int)c.size() - 1) {
                int newSz = sz;
                int newIdx = idx + 1;
                ll newSubv = subv - c[idx] + c[idx + 1];
                ll newV = newSubv;
                if(x - newSz - 1 >= 0) newV += pre[x - newSz - 1];
                pq.push({ newV, newSubv, newSz, newIdx, false });
            }

            // 뒤에 하나 추가하기
            if(sz < y && idx < (int)c.size() - 1) {
                int newSz = sz + 1;
                int newIdx = idx + 1;
                ll newSubv = subv + c[newIdx];
                ll newV = newSubv;
                if(x - newSz - 1 >= 0) newV += pre[x - newSz - 1];
                pq.push({ newV, newSubv, newSz, newIdx, false });
            }

            return kth[k];
        }
    };
    vector<Node> d(m);
    for(int i = 0; i < n; ++i) {
        int a, c;
        cin >> a >> c;
        a--;
        d[a].c.push_back(c);
    }
    for(auto& v : d) cin >> v.x >> v.y;

    ll init = 0;
    vector<Node> d2;
    for(int i = 0; i < m; ++i) {
        d[i].init();
        ll v = d[i].getKth(0);
        if(v < 0) {
            init = -1;
            break;
        }
        init += v;
        ll v2 = d[i].getKth(1);
        if(v2 >= 0) {
            d2.push_back(move(d[i]));
        }
    }
    sort(d2.begin(), d2.end(), [](Node& l, Node& r) {
        return l.getKth(1) - l.getKth(0) < r.getKth(1) - r.getKth(0);
    });
    n = d2.size();
    struct QNode
    {
        ll v;
        int idx;
        int kth;
        bool operator<(const QNode& rhs) const {
            return v > rhs.v;
        }
    };
    priority_queue<QNode> pq;
    if(init >= 0 && d2.size() > 0) {
        pq.push({ init - d2[0].getKth(0) + d2[0].getKth(1), 0, 1 });
    }

    cout << init << "\n";
    for(int i = 0; i < k - 1; ++i) {
        if(pq.empty() || pq.top().v < 0) {
            cout << "-1\n";
            continue;
        }
        auto [v, idx, kth] = pq.top();
        pq.pop();
        cout << v << "\n";

        // 다음 kth
        if(d2[idx].getKth(kth + 1) >= 0) {
            ll newv = v - d2[idx].getKth(kth) + d2[idx].getKth(kth + 1);
            pq.push({ newv, idx, kth + 1 });
        }

        // 다음 idx
        if(idx < n - 1) {
            // 다음 idx의 1번째 값
            ll newv = v - d2[idx + 1].getKth(0) + d2[idx + 1].getKth(1);
            pq.push({ newv, idx + 1, 1 });

            // 현재 idx의 1번째->0번째하고, 다음 idx의 1번째 값
            if(kth == 1) {
                ll newv = v - d2[idx].getKth(1) + d2[idx].getKth(0);
                newv += d2[idx + 1].getKth(1) - d2[idx + 1].getKth(0);
                pq.push({ newv, idx + 1, 1 });
            }
        }
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
