#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<pair<ll, int>> largePrimeFac(ll v)
{
    vector<pair<ll, int>> res;
    ll sqv = sqrtl(v);

    for(ll f = 2; f <= sqv && v > 1; ++f) {
        if(v % f != 0) continue;
        res.emplace_back(f, 0);
        while(v % f == 0) {
            res.back().second++;
            v /= f;
        }
    }
    if(v > 1) res.emplace_back(v, 1);

    return res;
}


void solve()
{
    int x, y;
    cin >> x >> y;
    if(x < y) swap(x, y);

    auto isPrime = [](int x) {
        int sqx = sqrt(x);
        for(int f = 2; f <= sqx; ++f) {
            if(x % f == 0) return false;
        }
        return true;
    };
    int res = INF;
    if(isPrime(x) || y < gcd(x, y)) {
        res = x + y;
    } else {
        struct Point
        {
            int x, y;
            bool operator<(Point rhs) const { return tie(x, y) < tie(rhs.x, rhs.y); }
        };
        set<Point> mp;
        vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };

        struct QNode
        {
            int x, y, cost;
        };
        queue<QNode> q;
        q.push({ x, y, 0 });
        mp.insert({ x, y });
        while(q.empty() == false) {
            auto [cx, cy, cost] = q.front();
            q.pop();

            int g = gcd(cx, cy);
            if(isPrime(cx) || cy < g) {
                res = min(res, cost + cx + cy);
                continue;
            }

            for(int i = 0; i < 4; ++i) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                if(nx < 0 || ny < 0 || cost + nx + ny > res) continue;
                if(gcd(nx, ny) != 1) continue;
                if(mp.find({ nx, ny }) != mp.end()) continue;

                q.push({ nx, ny, cost + 1 });
                mp.insert({ nx, ny });
            }
        }
    }

    if(res == INF) res = -1;
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
