#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Node
{
    int a, b, c, ab, bc, abc;
    Node() :
        a(0), b(0), c(0), ab(0), bc(0), abc(0)
    {}
};

struct SegTree
{
    int n;
    vector<Node> t;

    void init(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
        // Add init values in [n, n+n)
    }

    void initv(int idx, char ch)
    {
        t[n + idx] = Node();
        if(ch == 'a') t[n + idx].a = 1;
        else if(ch == 'b') t[n + idx].b = 1;
        else t[n + idx].c = 1;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, char ch)
    {
        idx += n;
        t[idx] = Node();
        if(ch == 'a') t[idx].a = 1;
        else if(ch == 'b') t[idx].b = 1;
        else t[idx].c = 1;

        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = emptyNode;
        Node resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    Node merge(Node l, Node r)
    {
        Node res;
        res.a = l.a + r.a;
        res.b = l.b + r.b;
        res.c = l.c + r.c;

        res.ab = l.a + r.ab;
        res.ab = min(res.ab, l.ab + r.b);
        res.bc = l.b + r.bc;
        res.bc = min(res.bc, l.bc + r.c);

        res.abc = l.a + r.abc;
        res.abc = min(res.abc, l.ab + r.bc);
        res.abc = min(res.abc, l.abc + r.c);

        return res;
    }

    const Node emptyNode = Node();
};


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    string str;
    cin >> str;

    SegTree sg;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.initv(i, str[i]);
    }
    sg.build();

    for(int i = 0; i < q; ++i) {
        int idx;
        char ch;
        cin >> idx >> ch;
        idx--;
        sg.update(idx, ch);

        cout << sg.find(0, n - 1).abc << "\n";
    }


    return 0;
}
