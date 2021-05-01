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
struct Node
{
    int dis;
    int x, y;
    int stopIdx;
    int blockIdx;
};

int n;
vector<Point> u, r;
int res[1001];
pair<int, int> blockPos;
vector<Node> d;

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
        res[i] = INF;
    }

    sort(r.begin(), r.end(), [](const Point& l, const Point& r) {
        return l.y < r.y;
    });
    sort(u.begin(), u.end(), [](const Point& l, const Point& r) {
        return l.x < r.x;
    });

    for(auto& cr : r) {
        for(auto& cu : u) {
            if(res[cr.idx] != INF || res[cu.idx] != INF) continue;
            if((cu.x < cr.x) || (cr.y < cu.y)) continue;
            int dx = cu.x - cr.x;
            int dy = cr.y - cu.y;
            if(dx < dy) {
                res[cu.idx] = dy;
            } else if(dx > dy) {
                res[cr.idx] = dx;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        if(res[i] == INF) cout << "Infinity\n";
        else cout << res[i] << "\n";
    }

    return 0;
}
