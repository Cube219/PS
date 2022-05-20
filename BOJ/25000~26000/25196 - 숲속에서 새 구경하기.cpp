#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Node
    {
        ll s, e, v;
        ll k;
    };
    Node a, b, c;
    cin >> a.v >> a.s >> a.e;
    cin >> b.v >> b.s >> b.e;
    cin >> c.v >> c.s >> c.e;

    a.k = 0;
    b.k = 0;
    c.k = 0;

    struct QNode
    {
        ll t;
        int isEnd;
        int type;
        bool operator<(const QNode& rhs) const
        {
            if(t == rhs.t) return isEnd < rhs.isEnd;
            return t > rhs.t;
        }
    };
    priority_queue<QNode> pq;
    pq.push({ a.s, 0, 0 });
    pq.push({ a.e + 1, 1, 0 });
    pq.push({ b.s, 0, 1 });
    pq.push({ b.e + 1, 1, 1 });
    pq.push({ c.s, 0, 2 });
    pq.push({ c.e + 1, 1, 2 });

    ll res = -1;
    int cnt = 0;
    while(1) {
        auto [t, isEnd, type] = pq.top();
        pq.pop();

        if(t > a.v * b.v * c.v * 3) break;

        if(isEnd) {
            cnt--;

            if(type == 0) {
                a.k++;
                pq.push({ a.s + a.v * a.k, 0, 0 });
                pq.push({ a.e + 1 + a.v * a.k, 1, 0 });
            } else if(type == 1) {
                b.k++;
                pq.push({ b.s + b.v * b.k, 0, 1 });
                pq.push({ b.e + 1 + b.v * b.k, 1, 1 });
            } else {
                c.k++;
                pq.push({ c.s + c.v * c.k, 0, 2 });
                pq.push({ c.e + 1 + c.v * c.k, 1, 2 });
            }
        } else {
            cnt++;
            if(cnt == 3) {
                res = t;
                break;
            }
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
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
