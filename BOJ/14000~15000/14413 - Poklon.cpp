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
int d[500001];
Query q[500001];
vector<int> idx;
int num[500001];
int res[500001];

int getIdx(int v)
{
    return lower_bound(idx.begin(), idx.end(), v) - idx.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    idx.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        idx[i] = d[i];
    }
    sort(idx.begin(), idx.end());
    idx.erase(unique(idx.begin(), idx.end()), idx.end());

    for(int i = 0; i < n; ++i) {
        d[i] = getIdx(d[i]);
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

    int cnt = 0;
    for(int i = q[0].l; i <= q[0].r; ++i) {
        num[d[i]]++;
        if(num[d[i]] == 2) cnt++;
        else if(num[d[i]] == 3) cnt--;
    }
    res[q[0].idx] = cnt;
    int l = q[0].l;
    int r = q[0].r;
    for(int i = 1; i < m; ++i) {
        int nl = q[i].l;
        int nr = q[i].r;
        while(nl < l) {
            l--;
            num[d[l]]++;
            if(num[d[l]] == 2) cnt++;
            else if(num[d[l]] == 3) cnt--;
        }
        while(r < nr) {
            r++;
            num[d[r]]++;
            if(num[d[r]] == 2) cnt++;
            else if(num[d[r]] == 3) cnt--;
        }
        while(l < nl) {
            if(num[d[l]] == 3) cnt++;
            else if(num[d[l]] == 2) cnt--;
            num[d[l]]--;
            l++;
        }
        while(nr < r) {
            if(num[d[r]] == 3) cnt++;
            else if(num[d[r]] == 2) cnt--;
            num[d[r]]--;
            r--;
        }
        res[q[i].idx] = cnt;
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
