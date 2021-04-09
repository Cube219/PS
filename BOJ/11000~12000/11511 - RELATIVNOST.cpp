#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int MOD = 10007;

int n, c;
int a[100001], b[100001];
int res;

struct Node
{
    bool has;
    int c[21];
};
Node zeroNode;

template <int N>
class SegTree
{
public:
    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }
    Node combine(Node& l, Node& r)
    {
        Node res;
        res.has = true;
        for(int i = 0; i < c; ++i) {
            res.c[i] = 0;
            if(r.has == false) {
                res.c[i] = l.c[i];
            } else {
                for(int j = 0; j <= i; ++j) {
                    res.c[i] = ((l.c[j] * r.c[i - j]) % MOD + res.c[i]) % MOD;
                }
            }
        }
        return res;
    }

    void addValue(int idx)
    {
        t[stLeaf + idx].c[0] = b[idx] % MOD;
        t[stLeaf + idx].c[1] = a[idx] % MOD;
        t[stLeaf + idx].has = true;
    }
    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = combine(t[i * 2], t[i * 2 + 1]);
            t[i].has = true;
        }
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return zeroNode;
        int m = (cl + cr) / 2;
        Node lnode = findImpl(cl, m, l, r, node * 2);
        Node rnode = findImpl(m + 1, cr, l, r, node * 2 + 1);
        return combine(lnode, rnode);
    }

    Node find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l)
    {
        int node = stLeaf + l;
        t[node].c[0] = b[l] % MOD;
        t[node].c[1] = a[l] % MOD;

        node /= 2;
        while(node > 0) {
            t[node] = combine(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

// (a / b) % mod == (a * b^(mod-2)) % mod
int divmod(int a, int b, int mod)
{
    int res = 1;
    int ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}

SegTree<100001> sg;
Node tmp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    res = 1;
    for(int i = 0; i < n; ++i) {
        res = ((a[i] + b[i]) % MOD * res) % MOD;
    }
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.addValue(i);
    }

    sg.init2();

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int p, na, nb;
        cin >> p >> na >> nb;
        p--;

        res = divmod(res, (a[p] + b[p]) % MOD, MOD);
        res = ((na + nb) % MOD * res) % MOD;

        a[p] = na;
        b[p] = nb;
        sg.update(p);

        tmp = sg.find(0, n - 1);
        int except = 0;
        for(int j = 0; j < c; ++j) {
            except = (except + tmp.c[j]) % MOD;
        }
        cout << (res - except + MOD) % MOD << "\n";
    }

    return 0;
}
