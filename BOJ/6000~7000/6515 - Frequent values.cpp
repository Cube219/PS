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

int tNum;
int n, m;
int d[100001];
Query q[100001];
int num[200001], num2[200001];
int curmax;
int res[100001];

void add(int v)
{
    num2[num[v]]--;
    num[v]++;
    num2[num[v]]++;
    curmax = max(curmax, num[v]);
}

void remove(int v)
{
    num2[num[v]]--;
    if(curmax == num[v] && num2[num[v]] == 0) {
        curmax--;
    }
    num[v]--;
    num2[num[v]]++;
}

void clear()
{
    for(int i = 0; i <= 200000; ++i) {
        num2[i] = 0;
        num[i] = 0;
    }
    curmax = 0;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;
        cin >> m;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            d[i] += 100000;
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
        num2[0] = 200000;
        for(int i = q[0].l; i <= q[0].r; ++i) {
            add(d[i]);
        }
        res[q[0].idx] = curmax;
        int l = q[0].l;
        int r = q[0].r;
        for(int i = 1; i < m; ++i) {
            int nl = q[i].l;
            int nr = q[i].r;
            while(nl < l) {
                l--;
                add(d[l]);
            }
            while(r < nr) {
                r++;
                add(d[r]);
            }
            while(l < nl) {
                remove(d[l]);
                l++;
            }
            while(nr < r) {
                remove(d[r]);
                r--;
            }
            res[q[i].idx] = curmax;
        }

        for(int i = 0; i < m; ++i) {
            cout << res[i] << "\n";
        }

        clear();
    }

    return 0;
}
