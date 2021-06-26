#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr double INF = 999999999999;

int n, m;
int d[1001];
vector<pair<int, int>> g[1001];
double dis[1001];
int cnt[1001];
bool inq[1001];

bool ck(double res)
{
    for(int i = 0; i < n; ++i) {
        dis[i] = INF;
        cnt[i] = 0;
        inq[i] = false;
    }
    dis[0] = 0;
    inq[0] = true;
    queue<int> q;
    q.push(0);

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        cnt[cur]++;
        if(cnt[cur] > n) {
            return false;
        }
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            double cost = (double)nx.second * res - (double)d[nxt];
            if(dis[nxt] > dis[cur] + cost) {
                dis[nxt] = dis[cur] + cost;
                if(inq[nxt] == false) {
                    q.push(nxt);
                    inq[nxt] = true;
                }
            }
        }
    }
    return true;
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
        cin >> d[i];
    }
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
    }

    double l = 0.0, r = 100000.0;
    for(int i = 0; i < 100; ++i) {
        double mid = (l + r) / 2.0;
        if(ck(mid) == true) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << fixed << setprecision(2) << l;

    return 0;
}
