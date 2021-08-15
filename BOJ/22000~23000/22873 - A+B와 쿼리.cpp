#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;
constexpr ll INF = 1000000000000;

template <int N>
class SegTree
{
public:
    struct Node
    {
        ll sum, mx, lmx, rmx;
    };
    Node t[N * 4];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { -INF, -INF, -INF, -INF };

        }
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = { v, v, v, v };
    }

    void build()
    {
        for(int i = stLeaf - 1; i >= 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node merge(Node left, Node right)
    {
        Node cur;
        cur.sum = left.sum + right.sum;
        cur.lmx = max(left.lmx, left.sum + right.lmx);
        cur.rmx = max(right.rmx, right.sum + left.rmx);
        cur.mx = left.rmx + right.lmx;
        cur.mx = max(cur.mx, left.mx);
        cur.mx = max(cur.mx, right.mx);
        return cur;
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return { -0, -0, -0, -0 };
        int m = (cl + cr) / 2;
        Node mnode = merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
        return mnode;
    }

    ll find(int l, int r)
    {
        Node res = findImpl(0, stLeaf - 1, l, r, 1);
        return res.mx;
    }

    void add(int l, ll v)
    {
        int node = stLeaf + l;
        t[node].sum += v;
        t[node].mx += v;
        t[node].lmx += v;
        t[node].rmx += v;

        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);

            node /= 2;
        }
    }

    void set(int l, ll v)
    {
        int node = stLeaf + l;
        t[node].sum = v;
        t[node].mx = v;
        t[node].lmx = v;
        t[node].rmx = v;

        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);

            node /= 2;
        }
    }
};

int n, q;
string s1, s2;
SegTree<300015> sg;
bool iscarry[300011];

ll num(int idx)
{
    ll v = sg.t[sg.stLeaf + idx].mx;
    sg.set(idx, INF);
    ll vv = sg.find(0, idx);
    ll res;
    if(vv > INF) {
        res = vv - INF;
    } else {
        res = 0;
    }
    sg.set(idx, v);
    return res;
}

bool iscarry9(int b)
{
    bool ic = false;
    sg.add(b, -1 + INF);
    ll idx = sg.find(b, n);
    if(idx >= INF) {
        idx -= INF;
        idx += b + 1;
        if(iscarry[idx] == true) {
            ic = true;
        }
    }
    sg.add(b, -INF + 1);
    return ic;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    cin >> s1 >> s2;

    sg.init(n + 1);

    for(int i = 0; i < n; ++i) {
        int a = s1[i] - '0';
        int b = s2[i] - '0';
        if(a + b == 9) {
            sg.initv(i + 1, 1);
        }
        if(a + b >= 10) iscarry[i + 1] = true;
    }
    sg.build();

    for(int i = 0; i < q; ++i) {
        char a;
        int b, c;
        cin >> a >> b >> c;
        b--;
        b = n - b - 1;
        int before, after;
        before = s1[b] - '0';
        before += s2[b] - '0';
        if(a == 'A') {
            s1[b] = c + '0';
        } else {
            s2[b] = c + '0';
        }
        after = s1[b] - '0';
        after += s2[b] - '0';

        ll res = 1;
        if(before == after) {
            cout << "0\n";
            continue;
        }
        b++;
        if(before == 9) {
            bool ic = iscarry9(b);

            if(ic == true) {
                if(after < 9) {
                    // carry down
                    res += num(b) + 1;
                } else if(after >= 10) {
                    // 원래 carry up 상태였음
                    iscarry[b] = true;
                }
            } else {
                if(after > 9) {
                    // carry up
                    res += num(b) + 1;
                    iscarry[b] = true;
                }
            }
            sg.set(b, -INF);
        } else if(before < 9) {
            if(after == 9) {
                sg.set(b, 1);
                bool ic = iscarry9(b);
                if(ic == true) {
                    // carry up
                    res += num(b) + 1;
                }
            } else if(after > 9) {
                iscarry[b] = true;
                // carry up
                res += num(b) + 1;
            }
        } else { // 10이상
            if(after < 10) {
                iscarry[b] = false;
            }
            if(after == 9) {
                sg.set(b, 1);
                bool ic = iscarry9(b);
                if(ic == false) {
                    // carry down
                    res += num(b) + 1;
                }
            } else if(after < 9) {
                // carry down
                res += num(b) + 1;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
