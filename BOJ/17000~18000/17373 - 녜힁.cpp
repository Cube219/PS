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
    int t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l)
    {
        int node = stLeaf + l;
        t[node] = 1;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Query
{
    int first;
    ll num;
    int idx;
};

int n, m, q;
int d[100001], num[1000001], lastidx[1000001], startquery[1000001];
int cnt[1000001], curcnt;
Query query[100001];
pair<int, int> res[100001];
SegTree<1000001> sg;

int getkth(int num)
{
    int l = 0, r = m;
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        int v = sg.find(0, mid);
        if(mid - v > num) {
            r = mid;
        } else {
            if(mid - v == num && sg.t[sg.stLeaf + mid] == 1) {
                r = mid;
            } else {
                l = mid;
            }
        }
    }
    return l;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        d[i]--;
    }

    for(int i = 0; i < m; ++i) {
        num[i] = m;
    }

    for(int i = n - 1; i >= 0; --i) {
        num[d[i]] = min(num[d[i]], m - curcnt);
        lastidx[d[i]] = i;

        if(cnt[d[i]] == 0) curcnt++;
        cnt[d[i]]++;
    }
    for(int i = 0; i < n; ++i) {
        cnt[d[i]] = 0;
    }

    for(int i = 0; i < q; ++i) {
        ll k;
        cin >> k;
        k--;
        query[i].num = k;
        query[i].idx = i;
    }
    sort(query, query + q, [](const Query& l, const Query& r) {
        return l.num < r.num;
    });

    ll cursum = 0, curidx = 0;
    for(int i = 0; i < q; ++i) {
        while(curidx < m && cursum + num[curidx] <= query[i].num) {
            cursum += num[curidx];
            curidx++;
            startquery[curidx] = i;
        }
        if(curidx == m) {
            res[query[i].idx] = { -2, -2 };
            query[i].first = -1;
            continue;
        }

        query[i].first = curidx;
        query[i].num -= cursum;
        int ridx = query[i].idx;
        res[ridx].first = query[i].first;
        res[ridx].second = query[i].num;
    }

    sg.init(m);

    for(int i = n - 1; i >= 0; --i) {
        if(lastidx[d[i]] == i) {
            curidx = startquery[d[i]];
            while(curidx < q && query[curidx].first == d[i]) {
                int ridx = query[curidx].idx;
                res[ridx].first = d[i];
                res[ridx].second = getkth(query[curidx].num);
                curidx++;
            }
        }
        sg.add(d[i]);
        cnt[d[i]] = 1;
    }

    for(int i = 0; i < q; ++i) {
        cout << res[i].first + 1 << " " << res[i].second + 1 << "\n";
    }


    return 0;
}
