#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
#include <list>
using namespace std;

using ll = long long int;

struct Query
{
    int l, r, idx;
};

int n, k, m, sqn;
int d[100001];
Query q[100001];
int num[100001], numsq[100001];
list<int> curnum[100001];
int res[100001];

void add(int v, int idx, bool isback)
{
    if(curnum[v].size() > 0) {
        int t = curnum[v].back() - curnum[v].front();
        num[t]--;
        numsq[t / sqn]--;
    }
    if(isback == false) curnum[v].push_front(idx);
    else curnum[v].push_back(idx);

    int t = curnum[v].back() - curnum[v].front();
    num[t]++;
    numsq[t / sqn]++;
}

void remove(int v, bool isback)
{
    int t = curnum[v].back() - curnum[v].front();
    num[t]--;
    numsq[t / sqn]--;
    if(isback == false) curnum[v].pop_front();
    else curnum[v].pop_back();

    if(curnum[v].size() > 0) {
        t = curnum[v].back() - curnum[v].front();
        num[t]++;
        numsq[t / sqn]++;
    }
}

int getRes()
{
    for(int i = n / sqn; i >= 0; --i) {
        if(numsq[i] > 0) {
            int st = sqn * (i + 1) - 1;
            if(st >= n) st = n - 1;
            for(int j = st; j >= sqn * i; --j) {
                if(num[j] > 0) return j;
            }
        }
    }
    return 0;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        q[i] = { a, b, i };
    }
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
        add(d[i], i, true);
    }
    res[q[0].idx] = getRes();

    for(int i = 1; i < m; ++i) {
        int cl = q[i].l;
        int cr = q[i].r;
        while(cl < l) {
            l--;
            add(d[l], l, false);
        }
        while(r < cr) {
            r++;
            add(d[r], r, true);
        }
        while(l < cl) {
            remove(d[l], false);
            l++;
        }
        while(cr < r) {
            remove(d[r], true);
            r--;
        }
        res[q[i].idx] = getRes();
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
