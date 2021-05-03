#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;

struct Node
{
    int v;
    int idx;
};

int tNum;
int n, m, x;
Node d[100001];
ll maxh;
ll h[100001];
int res[100001];
bool pos;
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m >> x;
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            d[i] = { a, i };
        }
        sort(d, d + n, [](const Node& l, const Node& r) {
            return l.v > r.v;
        });

        pos = true;
        maxh = 0;
        while(pq.empty() == false) pq.pop();

        for(int i = 0; i < m; ++i) {
            pq.push({ 0, i });
            h[i] = 0;
        }
        for(int i = 0; i < n; ++i) {
            auto cur = pq.top();
            pq.pop();

            res[d[i].idx] = cur.second;
            h[cur.second] += d[i].v;
            maxh = max(maxh, h[cur.second]);

            pq.push({ h[cur.second], cur.second });
        }
        int minh = pq.top().first;
        if(maxh - minh > x) {
            pos = false;
        }

        if(pos == false) cout << "NO\n";
        else {
            cout << "YES\n";
            for(int i = 0; i < n; ++i) {
                cout << res[i] + 1 << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
