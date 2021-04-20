#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

struct Query
{
    int l, r, idx;
};
int n, m, sqn;
int d[300001];
Query q[300001];
int res[300001];
int cnt[300001];
int num[300001];
int curmax;

void add(int v)
{
    num[cnt[v]]--;
    cnt[v]++;
    num[cnt[v]]++;
    curmax = max(curmax, cnt[v]);
}

void remove(int v)
{
    num[cnt[v]]--;
    if(curmax == cnt[v] && num[cnt[v]] == 0) {
        curmax--;
    }
    cnt[v]--;
    num[cnt[v]]++;
}

void process(Query& q)
{
    int totalNum = q.r - q.l + 1;
    if(curmax <= (totalNum + 1) / 2) {
        res[q.idx] = 1;
        return;
    }

    int otherNum = totalNum - curmax;
    res[q.idx] = curmax - otherNum;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        q[i] = { a, b, i };
    }
    num[0] = n;
    sqn = (int)sqrt(n);
    sort(q, q + m, [](const Query& l, const Query& r) {
        int ll = l.l / sqn;
        int rr = r.l / sqn;
        if(ll == rr) return l.r < r.r;
        return ll < rr;
    });

    int l = q[0].l;
    int r = q[0].r;
    for(int i = l; i <= r; ++i) {
        add(d[i]);
    }
    process(q[0]);

    for(int i = 1; i < m; ++i) {
        int cl = q[i].l;
        int cr = q[i].r;
        while(cl < l) {
            l--;
            add(d[l]);
        }
        while(r < cr) {
            r++;
            add(d[r]);
        }
        while(l < cl) {
            remove(d[l]);
            l++;
        }
        while(cr < r) {
            remove(d[r]);
            r--;
        }
        process(q[i]);
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
