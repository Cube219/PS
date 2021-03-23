#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll MOD = 1000000007;

template <int N>
class SegTree
{
public:
    ll t[N * 3], addlazy[N * 3], mullazy[N * 3], setlazy[N * 3];
    int stLeaf, n;

    void init(int n, ll* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = pData[i];
            mullazy[stLeaf + i] = 1;
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = (t[i * 2] + t[i * 2 + 1]) % MOD;
            mullazy[i] = 1;
        }
    }

    void propagate(int l, int r, int node)
    {
        if(addlazy[node] == 0 && mullazy[node] == 1 && setlazy[node] == 0) return;

        if(node < stLeaf) {
            int lnode = node * 2;
            int rnode = node * 2 + 1;
            if(setlazy[node] != 0) {
                setlazy[lnode] = setlazy[node];
                setlazy[rnode] = setlazy[node];
                addlazy[lnode] = addlazy[node];
                addlazy[rnode] = addlazy[node];
                mullazy[lnode] = mullazy[node];
                mullazy[rnode] = mullazy[node];
            } else {
                addlazy[lnode] = (addlazy[lnode] * mullazy[node]) % MOD;
                addlazy[rnode] = (addlazy[rnode] * mullazy[node]) % MOD;
                addlazy[lnode] = (addlazy[lnode] + addlazy[node]) % MOD;
                addlazy[rnode] = (addlazy[rnode] + addlazy[node]) % MOD;
                mullazy[lnode] = (mullazy[lnode] * mullazy[node]) % MOD;
                mullazy[rnode] = (mullazy[rnode] * mullazy[node]) % MOD;
            }
        }
        if(setlazy[node] > 0) {
            t[node] = (setlazy[node] * (ll)(r - l + 1)) % MOD;
        }
        t[node] = (t[node] * mullazy[node]) % MOD;
        t[node] = (t[node] + addlazy[node] * (ll)(r - l + 1)) % MOD;
        addlazy[node] = 0;
        mullazy[node] = 1;
        setlazy[node] = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return (findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1)) % MOD;
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v, int type)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            if(type == 0) {
                addlazy[node] = (addlazy[node] + v) % MOD;
            } else if(type == 1) {
                addlazy[node] = (addlazy[node] * v) % MOD;
                mullazy[node] = (mullazy[node] * v) % MOD;
            } else {
                addlazy[node] = 0;
                mullazy[node] = 1;
                setlazy[node] = v;
            }
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v, type);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v, type);
        t[node] = (t[node * 2] + t[node * 2 + 1]) % MOD;
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v, int type)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v, type);
    }
};

SegTree<100000> sg;
int n, m;
ll d[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sg.init(n, d);

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, x, y, v;
        cin >> a;
        if(a == 1) {
            cin >> x >> y >> v;
            sg.add(x - 1, y - 1, v, 0);
        } else if(a == 2) {
            cin >> x >> y >> v;
            sg.add(x - 1, y - 1, v, 1);
        } else if(a == 3) {
            cin >> x >> y >> v;
            sg.add(x - 1, y - 1, v, 2);
        } else {
            cin >> x >> y;
            cout << sg.find(x - 1, y - 1) << "\n";
        }
    }

    return 0;
}
