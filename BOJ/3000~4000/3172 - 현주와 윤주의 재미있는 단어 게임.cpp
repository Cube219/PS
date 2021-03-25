#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

template <int N>
class SegTree
{
public:
    ll t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n, ll* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            if(pData == nullptr) t[stLeaf + i] = 0;
            else t[stLeaf + i] = pData[i];
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += (r - l + 1) * lazy[node];
        lazy[node] = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

SegTree<100000> sg;

int n;
vector<pair<string, int>> d;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        d.push_back({ std::move(str), 0 });
    }
    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.first < r.first;
    });
    for(int i = 0; i < d.size(); ++i) {
        d[i].second = i;
        reverse(d[i].first.begin(), d[i].first.end());
    }
    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.first < r.first;
    });

    sg.init(n, nullptr);
    ll res = 0;
    for(int i = 0; i < d.size(); ++i) {
        res += sg.find(d[i].second, n - 1);
        sg.add(d[i].second, d[i].second, 1);
    }

    cout << res;

    return 0;
}
