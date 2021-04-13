#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct LRNode
{
    int len;
    ll mask;
};

struct Node
{
    vector<LRNode> left;
    vector<LRNode> right;
    int len;
    int value;
};

ll allMask;

class SegTree
{
public:
    Node t[100000 * 3];
    int stLeaf, n;

    void merge(int node)
    {
        Node& cur = t[node];
        Node& lnode = t[node * 2];
        Node& rnode = t[node * 2 + 1];

        int v = INF;
        int rIdx = rnode.left.size() - 1;
        for(int i = 0; i < lnode.right.size() && rIdx >= 0; ++i) {
            ll mask = lnode.right[i].mask | rnode.left[rIdx].mask;
            if(mask == allMask) {
                v = min(v, lnode.right[i].len + rnode.left[rIdx].len);
                rIdx--;
                i--;
            }
        }
        cur.value = min(lnode.value, rnode.value);
        cur.value = min(cur.value, v);
        cur.len = lnode.len + rnode.len;

        cur.left.clear();
        cur.left.assign(lnode.left.begin(), lnode.left.end());
        ll curMask;
        if(cur.left.size() > 0) curMask = cur.left.back().mask;
        for(int i = 0; i < rnode.left.size(); ++i) {
            ll mask = curMask | rnode.left[i].mask;
            if(mask != curMask) {
                cur.left.push_back({ lnode.len + rnode.left[i].len, mask });
                curMask = mask;
            }
        }

        cur.right.clear();
        cur.right.assign(rnode.right.begin(), rnode.right.end());
        if(cur.right.size() > 0) curMask = cur.right.back().mask;
        for(int i = 0; i < lnode.right.size(); ++i) {
            ll mask = curMask | lnode.right[i].mask;
            if(mask != curMask) {
                cur.right.push_back({ rnode.len + lnode.right[i].len, mask });
                curMask = mask;
            }
        }
    }

    void init(int n, int* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i].len = 1;
            t[stLeaf + i].left.push_back({ 1, 1ll << pData[i] });
            t[stLeaf + i].right.push_back({ 1, 1ll << pData[i] });
        }
        for(int i = stLeaf * 2; i > 0; --i) {
            t[i].value = INF;
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            merge(i);
        }
    }

    void update(int idx, int v)
    {
        int node = stLeaf + idx;
        t[node].left[0].mask = 1ll << v;
        t[node].right[0].mask = 1ll << v;
        node /= 2;
        while(node > 0) {
            merge(node);
            node /= 2;
        }
    }
};

SegTree sg;
int n, k, m;
int d[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> m;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        d[i]--;
    }
    allMask = 1ll << k;
    allMask--;
    sg.init(n, d);

    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int b, c;
            cin >> b >> c;
            b--; c--;
            sg.update(b, c);
        } else {
            if(k == 1) cout << "1\n";
            else {
                int res = sg.t[1].value;
                if(res == INF) res = -1;
                cout << res << "\n";
            }
        }
    }

    return 0;
}
