#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 1000000000000000005;

struct Node
{
    int x, y;
};

int n, m;
vector<Node> a, b, aa, bb;
ll res;

void dnq(int s, int e, int minj, int maxj)
{
    if(s > e) return;

    int i = (s + e) / 2;
    ll r = -INF;
    int midj = minj;
    for(int j = minj; j <= maxj; ++j) {
        if(r == -INF && bb[j].x <= aa[i].x) {
            midj = j;
            continue;
        }
        if(bb[j].y <= aa[i].y) continue;
        ll v = (ll)(bb[j].x - aa[i].x) * (bb[j].y - aa[i].y);
        if(r < v) {
            r = v;
            midj = j;
        }
    }
    res = max(res, r);

    dnq(s, i - 1, midj, maxj);
    dnq(i + 1, e, minj, midj);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    a.resize(n); b.resize(m);
    for(auto& v : a) cin >> v.x >> v.y;
    for(auto& v : b) cin >> v.x >> v.y;

    sort(a.begin(), a.end(), [](const Node& l, const Node& r) {
        if(l.y == r.y) return l.x < r.x;
        return l.y < r.y;
    });
    sort(b.begin(), b.end(), [](const Node& l, const Node& r) {
        if(l.y == r.y) return l.x > r.x;
        return l.y > r.y;
    });

    for(auto& v : a) {
        if(aa.size() == 0 || aa.back().x > v.x) aa.push_back(v);
    }
    for(auto& v : b) {
        if(bb.size() == 0 || bb.back().x < v.x) bb.push_back(v);
    }

    dnq(0, aa.size() - 1, 0, bb.size() - 1);

    cout << res;

    return 0;
}
