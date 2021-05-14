#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999;

struct SNode
{
    ll v;
    int key;
};

template <int N>
class SegTree
{
public:
    SNode t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = { INF, -1 };
        }

    }
    void addValue(int idx, SNode d)
    {
        t[stLeaf + idx] = d;
    }
    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            if(t[i * 2].v < t[i * 2 + 1].v) {
                t[i] = t[i * 2];
            } else {
                t[i] = t[i * 2 + 1];
            }
        }
    }

    SNode findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return { INF, -1 };
        int m = (cl + cr) / 2;

        SNode left = findImpl(cl, m, l, r, node * 2);
        SNode right = findImpl(m + 1, cr, l, r, node * 2 + 1);
        if(left.v < right.v) {
            return left;
        } else {
            return right;
        }
    }

    SNode find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[node].v = v;
        node /= 2;
        while(node > 0) {
            if(t[node * 2].v < t[node * 2 + 1].v) {
                t[node] = t[node * 2];
            } else {
                t[node] = t[node * 2 + 1];
            }
            node /= 2;
        }
    }
};

struct Node
{
    int r, g, b, key;
};

int n;
Node d[100001];
set<pair<int, int>> r, g, b;
ll rv[100001], gv[100001], bv[100001];
int rnum[361], gnum[361], bnum[361];
SegTree<100001> sg;

vector<int> kk;
int getk(int v)
{
    return lower_bound(kk.begin(), kk.end(), v) - kk.begin();
}

void updateangle(set<pair<int, int>>& s, set<pair<int, int>>::iterator it, ll* v, int* num)
{
    auto bit = it;
    if(bit == s.begin()) {
        bit = s.end();
    }
    --bit;
    auto ait = it;
    ++ait;
    if(ait == s.end()) ait = s.begin();
    int langle = ait->first;
    int angle = it->first;
    int rangle = bit->first;

    if(langle < angle) langle += 360;
    if(angle < rangle) rangle -= 360;
    v[it->second] = langle - angle;
    v[it->second] += angle - rangle;
    if(num[it->first] > 1) {
        v[it->second] = 0;
    }
}

void buildset(set<pair<int, int>>& s, ll* v, int* num)
{
    for(auto it = s.begin(); it != s.end(); ++it) {
        updateangle(s, it, v, num);
    }
}

void eraseset(set<pair<int, int>>& s, pair<int, int> key, ll* v, int* num)
{
    auto it = s.find(key);
    auto bit = it;
    if(bit == s.begin()) {
        bit = s.end();
    }
    --bit;
    auto ait = it;
    ++ait;
    if(ait == s.end()) ait = s.begin();

    sg.update(it->second, INF);
    num[it->first]--;
    s.erase(it);
    updateangle(s, bit, v, num);
    updateangle(s, ait, v, num);
    sg.update(bit->second, rv[bit->second] + gv[bit->second] + bv[bit->second]);
    sg.update(ait->second, rv[ait->second] + gv[ait->second] + bv[ait->second]);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].r >> d[i].g >> d[i].b >> d[i].key;
        kk.push_back(d[i].key);
    }
    sort(kk.begin(), kk.end());
    kk.erase(unique(kk.begin(), kk.end()), kk.end());
    for(int i = 0; i < n; ++i) {
        d[i].key = getk(d[i].key);
        r.insert({ d[i].r, d[i].key });
        g.insert({ d[i].g, d[i].key });
        b.insert({ d[i].b, d[i].key });
        rnum[d[i].r]++;
        gnum[d[i].g]++;
        bnum[d[i].b]++;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.key < r.key;
    });
    buildset(r, rv, rnum);
    buildset(g, gv, gnum);
    buildset(b, bv, bnum);
    for(int i = 0; i < n; ++i) {
        if(rnum[d[i].r] > 1) {
            rv[i] = 0;
        }
        if(gnum[d[i].g] > 1) {
            gv[i] = 0;
        }
        if(bnum[d[i].b] > 1) {
            bv[i] = 0;
        }
    }

    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.addValue(i, { rv[i] + gv[i] + bv[i], i });
    }
    sg.build();
    vector<int> res;
    for(int i = n - 1; i >= 0; --i) {
        SNode cur = sg.find(0, n - 1);
        res.push_back(kk[cur.key]);
        if(i == 0) break;
        eraseset(r, { d[cur.key].r, cur.key }, rv, rnum);
        eraseset(g, { d[cur.key].g, cur.key }, gv, gnum);
        eraseset(b, { d[cur.key].b, cur.key }, bv, bnum);
    }

    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
