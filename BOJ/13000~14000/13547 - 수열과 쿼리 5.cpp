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
    int l, r;
    int idx;
};

int n, m;
int d[100001];
Query q[100001];
int sqn;
int has[1000001];
int res[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
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

    int cnt = 0;
    for(int i = q[0].l; i <= q[0].r; ++i) {
        if(has[d[i]] == 0) cnt++;
        has[d[i]]++;
    }
    res[q[0].idx] = cnt;
    int l = q[0].l;
    int r = q[0].r;
    
    for(int i = 1; i < m; ++i) {
        int nl = q[i].l;
        int nr = q[i].r;
        while(nl < l) {
            l--;
            if(has[d[l]] == 0) cnt++;
            has[d[l]]++;
        }
        while(r < nr) {
            r++;
            if(has[d[r]] == 0) cnt++;
            has[d[r]]++;
        }
        while(l < nl) {
            has[d[l]]--;
            if(has[d[l]] == 0) cnt--;
            l++;
        }
        while(nr < r) {
            has[d[r]]--;
            if(has[d[r]] == 0) cnt--;
            r--;
        }
        res[q[i].idx] = cnt;
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
