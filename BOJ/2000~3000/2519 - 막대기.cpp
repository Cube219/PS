#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Point
{
    ll x, y;
};

Point operator+(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

ll dot(const Point& l, const Point& r)
{
    return l.x * r.x + l.y * r.y;
}

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

ll lensq(Point& a, Point& b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}

bool isCross(Point l1p1, Point l1p2, Point l2p1, Point l2p2)
{
    Point line = l1p2 - l1p1;
    Point a = l2p1 - l1p2;
    Point b = l2p2 - l1p2;
    ll cwa = ccw(line, a);
    ll cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    if(cwa == 0 && cwb == 0) {
        if(l1p1.x > l1p2.x) swap(l1p1.x, l1p2.x);
        if(l1p1.y > l1p2.y) swap(l1p1.y, l1p2.y);
        if(l2p1.x > l2p2.x) swap(l2p1.x, l2p2.x);
        if(l2p1.y > l2p2.y) swap(l2p1.y, l2p2.y);

        if(l1p2.x < l2p1.x) return false;
        if(l2p2.x < l1p1.x) return false;
        if(l1p2.y < l2p1.y) return false;
        if(l2p2.y < l1p1.y) return false;

        return true;
    }

    line = l2p2 - l2p1;
    a = l1p1 - l2p2;
    b = l1p2 - l2p2;
    cwa = ccw(line, a);
    cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    return true;
}

vector<int> g[6001];

int d[6001], dNum = 1;
bool finish[6001];
vector<int> st;
vector<vector<int>> sccs;
int sccIdx[6001];

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        sccs.push_back({});
        auto& scc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            scc.push_back(top);
            sccIdx[top] = sccs.size();
            finish[top] = true;

            if(top == cur) break;
        }
    }
    return ret;
}

int rev(int v)
{
    if(v % 2 == 0) return v + 1;
    return v - 1;
}

struct Line
{
    Point p1, p2;
};

int n;
Line l[1001][3];
int r[3001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            l[i][j].p1 = { x1, y1 };
            l[i][j].p2 = { x2, y2 };
        }
        g[i * 3 * 2].push_back(rev((i * 3 + 1) * 2));
        g[i * 3 * 2].push_back(rev((i * 3 + 2) * 2));
        g[(i * 3 + 1) * 2].push_back(rev((i * 3) * 2));
        g[(i * 3 + 1) * 2].push_back(rev((i * 3 + 2) * 2));
        g[(i * 3 + 2) * 2].push_back(rev((i * 3) * 2));
        g[(i * 3 + 2) * 2].push_back(rev((i * 3 + 1) * 2));
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int z1 = 0; z1 < 3; ++z1) {
                for(int z2 = 0; z2 < 3; ++z2) {
                    if(i == j && z1 == z2) continue;
                    if(isCross(l[i][z1].p1, l[i][z1].p2, l[j][z2].p1, l[j][z2].p2) == true) {
                        g[rev((i * 3 + z1) * 2)].push_back((j * 3 + z2) * 2);
                        g[rev((j * 3 + z2) * 2)].push_back((i * 3 + z1) * 2);
                    }
                }
            }
        }
    }

    for(int i = 0; i < n * 6; ++i) {
        if(d[i] == 0) dfs(i);
    }

    bool res = true;
    for(int i = 0; i < n * 6; i += 2) {
        if(sccIdx[i] == sccIdx[i + 1]) {
            res = false;
        }
    }
    if(res == true) {
        for(int i = sccs.size() - 1; i >= 0; i--) {
            auto& scc = sccs[i];
            for(int j = 0; j < scc.size(); ++j) {
                int cur = scc[j] / 2;
                if(r[cur] == 0) {
                    if(scc[j] % 2 == 0) {
                        r[cur] = 1;
                    } else {
                        r[cur] = -1;
                    }
                }
            }
        }
        vector<int> res;
        for(int i = 0; i < n * 3; ++i) {
            if(r[i] == -1) {
                res.push_back(i + 1);
            }
        }
        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
    } else {
        cout << "-1";
    }


    return 0;
}
