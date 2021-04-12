#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

ll n, m, k;
ll x[100001], y[100001], r[100001];
ll res;
struct Node
{
    ll l, r;
};
vector<Node> area[100001];

ll p(ll x, ll l, ll r)
{
    ll ret = r - l + 1;
    for(int i = 0; i < area[x].size(); ++i) {
        Node& n = area[x][i];
        if(n.r < l || r < n.l) continue;

        if(n.l <= l && r <= n.r) {
            ret = 0;
            break;
        }
        if(l <= n.l && n.r <= r) ret -= n.r - n.l + 1;
        else if(n.l <= l) ret -= n.r - l + 1;
        else if(r <= n.r) ret -= r - n.l + 1;
    }
    if(ret < 0) {
        ret = 0;
    }
    return ret;
}
void uni(ll x, ll l, ll r)
{
    area[x].push_back({ l, r });
    sort(area[x].begin(), area[x].end(), [](const Node& l, const Node& r) {
        if(l.l == r.l) return l.r < r.r;
        return l.l < r.l;
    });

    vector<Node> tmp;
    Node cur = area[x][0];
    for(int i = 1; i < area[x].size(); ++i) {
        Node& nxt = area[x][i];
        if(cur.r + 1 < nxt.l) {
            tmp.push_back(cur);
            cur = nxt;
        } else {
            cur.r = max(cur.r, nxt.r);
        }
    }
    tmp.push_back(cur);
    area[x].clear();
    area[x].assign(tmp.begin(), tmp.end());
}

void getCircle(vector<pair<ll, Node>>& d, ll radius)
{
    d.clear();
    for(ll i = -radius; i <= radius; ++i) {
        ll j = (ll)sqrt(radius*radius - i*i);
        d.push_back({ i, {-j, j} });
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 0; i < k; ++i) {
        cin >> x[i] >> y[i] >> r[i];
    }
    res = n * m * k;
    vector<pair<ll, Node>> cur;
    for(ll z = k - 1; z >= 0; --z) {
        cur.clear();
        ll curx = x[z];
        ll cury = y[z];
        ll curr = r[z];

        getCircle(cur, curr);
        for(int i = 0; i < cur.size(); ++i) {
            cur[i].first += curx;
            cur[i].second.l += cury;
            cur[i].second.r += cury;
        }

        ll cnt = 0;
        for(int i = 0; i < cur.size(); ++i) {
            cnt += p(cur[i].first, cur[i].second.l, cur[i].second.r);
        }
        res -= cnt * (z + 1);
        for(int i = 0; i < cur.size(); ++i) {
            uni(cur[i].first, cur[i].second.l, cur[i].second.r);
        }
    }

    cout << res;

    return 0;
}
