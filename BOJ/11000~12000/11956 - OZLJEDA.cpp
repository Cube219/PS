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
            t[i] = t[i * 2] ^ t[i * 2 + 1];
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) ^ findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }
};

int k, q;
ll d[100001];
SegTree<100001> sg;
ll m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k;
    for(int i = 0; i < k; ++i) {
        cin >> d[i];
        m ^= d[i];
    }
    sg.init(k, d);
    cin >> q;
    for(int i = 0; i < q; ++i) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        a %= (k + 1);
        b %= (k + 1);

        ll res = 0;
        if(a <= b) {
            if(b == k) {
                b--;
                res = m;
            }
            if(a <= b) res ^= sg.find(a, b);
        } else {
            int na = b + 1;
            int nb = a - 1;
            if(na <= nb) res = sg.find(na, nb);
        }
        cout << res << "\n";
    }

    return 0;
}
