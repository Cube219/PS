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

int n, m;
int d[100001];
Query q[100001];
int num[1000001];
ll res[100001];

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
    int sqn = (int)sqrt(n);
    sort(q, q + m, [sqn](const Query& l, const Query& r) {
        int ll = l.l / sqn;
        int rr = r.l / sqn;
        if(ll == rr) return l.r < r.r;
        return ll < rr;
    });

    ll cur = 0;
    for(int i = q[0].l; i <= q[0].r; ++i) {
        int v = d[i];
        cur -= (ll)num[v] * num[v] * v;
        num[v]++;
        cur += (ll)num[v] * num[v] * v;
    }
    res[q[0].idx] = cur;
    int l = q[0].l;
    int r = q[0].r;
    for(int i = 1; i < m; ++i) {
        int nl = q[i].l;
        int nr = q[i].r;
        while(nl < l) {
            l--;
            cur -= (ll)num[d[l]] * num[d[l]] * d[l];
            num[d[l]]++;
            cur += (ll)num[d[l]] * num[d[l]] * d[l];
        }
        while(r < nr) {
            r++;
            cur -= (ll)num[d[r]] * num[d[r]] * d[r];
            num[d[r]]++;
            cur += (ll)num[d[r]] * num[d[r]] * d[r];
        }
        while(l < nl) {
            cur -= (ll)num[d[l]] * num[d[l]] * d[l];
            num[d[l]]--;
            cur += (ll)num[d[l]] * num[d[l]] * d[l];
            l++;
        }
        while(nr < r) {
            cur -= (ll)num[d[r]] * num[d[r]] * d[r];
            num[d[r]]--;
            cur += (ll)num[d[r]] * num[d[r]] * d[r];
            r--;
        }
        res[q[i].idx] = cur;
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
