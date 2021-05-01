#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 2000000000;

struct Point
{
    int x, y, idx;
};

int n;
vector<Point> u, r;
int res[1001];
vector<int> g[1001];
bool finish[1001];
bool ishit[1001];

int dfs(int cur, int par)
{
    res[cur] = 1;
    finish[cur] = true;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        res[cur] += dfs(nxt, cur);
    }
    return res[cur];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        char a;
        int b, c;
        cin >> a >> b >> c;
        if(a == 'E') {
            r.push_back({ b, c, i });
        } else {
            u.push_back({ b, c, i });
        }
    }

    sort(r.begin(), r.end(), [](const Point& l, const Point& r) {
        return l.y < r.y;
    });
    sort(u.begin(), u.end(), [](const Point& l, const Point& r) {
        return l.x < r.x;
    });

    for(auto& cr : r) {
        for(auto& cu : u) {
            if(ishit[cr.idx] == true || ishit[cu.idx] == true) continue;
            if((cu.x < cr.x) || (cr.y < cu.y)) continue;
            int dx = cu.x - cr.x;
            int dy = cr.y - cu.y;
            if(dx < dy) {
                res[cu.idx] = cr.idx;
                ishit[cu.idx] = true;
                g[cr.idx].push_back(cu.idx);
            } else if(dx > dy) {
                res[cr.idx] = cu.idx;
                ishit[cr.idx] = true;
                g[cu.idx].push_back(cr.idx);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        if(finish[i] == true) continue;
        dfs(i, -1);
    }

    for(int i = 0; i < n; ++i) {
        cout << res[i] - 1 << "\n";
    }

    return 0;
}
