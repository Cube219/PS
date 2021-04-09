#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
class SegTree
{
public:
    ll t[N * 3];
    int stLeaf, n;

    void init(int n, ll* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = pData[i];
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, ll v)
    {
        int node = stLeaf + l;
        t[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Query1
{
    int idx;
    int v;
};

struct Query2
{
    int idx;
    int order;
    int l;
    int r;
};

SegTree<100001> sg;
int n, m;
ll d[100001];
vector<Query1> q1;
vector<Query2> q2;
ll res[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sg.init(n, d);

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int b, c;
            cin >> b >> c;
            q1.push_back({ b - 1, c });
        } else {
            int b, c, d;
            cin >> b >> c >> d;
            q2.push_back({ (int)q2.size(), b, c - 1, d - 1 });
        }
    }
    sort(q2.begin(), q2.end(), [](const auto& l, const auto& r) {
        return l.order < r.order;
    });
    q2.push_back({ 987654321, 987654321, 0, 0 });
    
    int q2Idx = 0;
    while(1) {
        Query2& q = q2[q2Idx];
        if(q.order > 0) break;
        res[q.idx] = sg.find(q.l, q.r);
        q2Idx++;
    }
    for(int i = 0; i < q1.size(); ++i) {
        while(q2[q2Idx].order == i) {
            Query2& q = q2[q2Idx];
            res[q.idx] = sg.find(q.l, q.r);
            q2Idx++;
        }
        sg.add(q1[i].idx, q1[i].v);
    }
    while(q2[q2Idx].order == q1.size()) {
        Query2& q = q2[q2Idx];
        res[q.idx] = sg.find(q.l, q.r);
        q2Idx++;
    }

    for(int i = 0; i < q2.size() - 1; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
