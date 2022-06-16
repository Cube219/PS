#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

template <bool isMax>
struct SegTree
{
    using Type = int;

    Type merge(Type l, Type r)
    {
        if(isMax) return max(l, r);
        return min(l, r);
    }

    Type emptyNode = INF;

    int n;
    vector<Type> t;

    SegTree(int _n)
    {
        if(isMax) emptyNode = 0;
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, Type v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, Type v)
    {
        idx += n;
        t[idx] = v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Type query(int l, int r)
    {
        l += n;
        r += n + 1;
        Type resl = emptyNode;
        Type resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n), pos(n + 1);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        pos[d[i]] = i;
    }

    SegTree<false> hSeg(n);
    SegTree<true> lMx(n);
    for(int i = 0; i < n; ++i) {
        hSeg.initv(i, d[i]);
    }
    hSeg.build();

    cout << "0\n";
    int res = 0;
    vector<int> dx(n + 1, 0);
    pos[0] = -1;
    for(int i = 1; i <= n; ++i) {
        if(pos[i] > 0) {
            int ll = lMx.query(0, pos[i] - 1);
            // [pos[ll] + 1, pos[i] - 1]
            if(pos[ll] + 1 <= pos[i] - 1) {
                int mn = hSeg.query(pos[ll] + 1, pos[i] - 1);

                if(mn != INF && hSeg.query(0, pos[mn]) >= mn) {
                    int st = i;
                    int ed = hSeg.query(0, pos[i] - 1);
                    if(st < ed) {
                        dx[st]++;
                        if(ed != INF) {
                            dx[ed]--;
                        } else {
                            dx[st]--;
                        }
                    }
                }
            }
        }

        lMx.update(pos[i], i);
        hSeg.update(pos[i], INF);

        res += dx[i];
        cout << res << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
