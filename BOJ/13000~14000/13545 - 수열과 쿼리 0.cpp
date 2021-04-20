#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>
using namespace std;

using ll = long long int;

struct Query
{
    int l, r, idx;
};

int n, m, sqn, sqsize;
int d[101001];
Query q[101001];
list<int> idxList[201001];
int num[101001], numsq[101001];
int res[101001];

void add(int v, int idx, bool isback)
{
    v += 100000;
    if(idxList[v].size() > 0) {
        int t = idxList[v].back() - idxList[v].front();
        num[t]--;
        numsq[t / sqn]--;
    }
    if(isback == true) idxList[v].push_back(idx);
    else idxList[v].push_front(idx);

    int t = idxList[v].back() - idxList[v].front();
    num[t]++;
    numsq[t / sqn]++;
}
void remove(int v, bool isback)
{
    v += 100000;
    int t = idxList[v].back() - idxList[v].front();
    num[t]--;
    numsq[t / sqn]--;
    if(isback == true) idxList[v].pop_back();
    else idxList[v].pop_front();

    if(idxList[v].size() > 0) {
        int t = idxList[v].back() - idxList[v].front();
        num[t]++;
        numsq[t / sqn]++;
    }
}

int getRes()
{
    for(int i = sqsize - 1; i >= 0; --i) {
        if(numsq[i] > 0) {
            for(int j = sqn * (i + 1) - 1; j >= sqn * i; --j) {
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

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        q[i] = { a - 1, b, i };
    }

    for(int i = 1; i <= n; ++i) {
        d[i] += d[i - 1];
    }
    sqn = (int)sqrt(n);
    sqsize = n / sqn + 1;
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
