#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

constexpr ll INF = 99999999999999;

template <int N>
class SegTree
{
public:
    ll t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = INF;
        }
        for(int i = 0; i < stLeaf; ++i) {
            t[i] = INF;
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return INF;
        int m = (cl + cr) / 2;
        return min(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, ll v)
    {
        int node = stLeaf + l;
        t[node] = min(v, t[node]);
        node /= 2;
        while(node > 0) {
            t[node] = min(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

struct Node
{
    ll a, b, c;
    int idx;
};

int n, m;
int c1, c2, c3;
Node d[100001];
vector<pair<int, int>> g[100001];
bool res[100001];
vector<ll> bIdx;
SegTree<100000> sg;

ll dst[100001];
bool visit[100001];
void dijk(int st)
{
    for(int i = 0; i < n; ++i) {
        dst[i] = INF;
        visit[i] = false;
    }
    dst[st] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            int cost = nx.second;

            if(visit[nxt] == false && dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                pq.push({ dst[nxt], nxt });
            }
        }
    }
}

int getBIdx(ll v)
{
    return lower_bound(bIdx.begin(), bIdx.end(), v) - bIdx.begin();
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c1 >> c2 >> c3 >> m;
    c1--; c2--; c3--;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    dijk(c1);
    for(int i = 0; i < n; ++i) {
        d[i].a = dst[i];
        d[i].idx = i;
    }
    dijk(c2);
    for(int i = 0; i < n; ++i) {
        d[i].b = dst[i];
        bIdx.push_back(dst[i]);
    }
    dijk(c3);
    for(int i = 0; i < n; ++i) {
        d[i].c = dst[i];
    }
    sort(d, d + n, [](const auto& l, const auto& r) {
        return l.a < r.a;
    });

    sort(bIdx.begin(), bIdx.end());
    bIdx.erase(unique(bIdx.begin(), bIdx.end()));
    for(int i = 0; i < n; ++i) {
        d[i].b = getBIdx(d[i].b);
    }

    for(int i = 0; i < n; ++i) {
        res[i] = true;
    }

    sg.init(bIdx.size());
    ll lastA = d[0].a;
    int lastAIdx = 0;
    int idx = 1;
    while(d[idx - 1].a == d[idx].a && idx < n) idx++;
    while(idx < n) {
        if(lastA != d[idx].a) {
            for(int i = lastAIdx; i < idx; ++i) {
                sg.add(d[i].b, d[i].c);
            }
            lastA = d[idx].a;
            lastAIdx = idx;
        }
        ll v = sg.find(0, d[idx].b - 1);
        if(v < d[idx].c) {
            res[d[idx].idx] = false;
        }
        idx++;
    }

    int qNum;
    cin >> qNum;
    for(int i = 0; i < qNum; ++i) {
        int q;
        cin >> q;
        if(res[q - 1] == false) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
