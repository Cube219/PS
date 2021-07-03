#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;
constexpr double INF = 99999999999999.0;

struct Node
{
    int x, y;
    int floor;
};

int n, m, q;
Node p[201];
vector<pair<int, double>> g[201];

double dst[201];
bool visit[201];
int rec[201];

void dijk(int st)
{
    for(int i = 0; i < n; ++i) {
        dst[i] = INF;
        visit[i] = false;
        rec[i] = -1;
    }
    dst[st] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            double cost = nx.second;

            if(visit[nxt] == false && dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                rec[nxt] = cur;
                pq.push({ dst[nxt], nxt });
            }
        }
    }
}


void process(int st, int ed)
{
    dijk(st);

    vector<int> res;
    int cur = ed;
    while(cur != st) {
        assert(cur != -1);
        res.push_back(cur);
        cur = rec[cur];
    }
    res.push_back(st);
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i] << " ";
    }
    cout << "\n";
}

void update(int a, int b, long double v)
{
    g[a].push_back({ b, v });
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> p[i].floor >> p[i].x >> p[i].y;
    }

    for(int i = 0; i < m; ++i) {
        int a, b;
        string str;
        cin >> a >> b >> str;
        if(str[0] == 'w' || str[0] == 's') {
            double dx = p[a].x - p[b].x;
            double dy = p[a].y - p[b].y;
            double dz = p[a].floor - p[b].floor;
            dz *= 5;
            double dis = sqrt(dx * dx + dy * dy + dz * dz);
            update(a, b, dis);
            update(b, a, dis);
        } else if(str[0] == 'l') {
            update(a, b, 1);
            update(b, a, 1);
        } else { // e
            double dx = p[a].x - p[b].x;
            double dy = p[a].y - p[b].y;
            double dz = p[a].floor - p[b].floor;
            dz *= 5;
            double dis = sqrt(dx * dx + dy * dy + dz * dz);

            update(a, b, 1);
            update(b, a, dis * 3);
        }
    }

    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        process(a, b);
    }

    return 0;
}
