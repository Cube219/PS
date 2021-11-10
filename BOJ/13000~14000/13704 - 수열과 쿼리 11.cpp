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

int n, k, a[100001], m, nsq;
Query q[100001];
ll res[100001];
int cnt[1 << 20];
ll curr;

void add(int v)
{
    curr += cnt[k ^ v];
    cnt[v]++;
}

void remove(int v)
{
    cnt[v]--;
    curr -= cnt[k ^ v];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    nsq = (int)sqrt(n);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        q[i] = { l, r, i };
    }
    sort(q, q + m, [](const Query& l, const Query& r) {
        if(l.l / nsq == r.l / nsq) return l.r < r.r;
        return l.l < r.l;
    });

    int l = q[0].l, r = q[0].l - 1;
    for(int i = 0; i < m; ++i) {
        auto& cur = q[i];

        while(cur.l < l) add(a[--l]);
        while(r < cur.r) add(a[++r]);
        while(l < cur.l) remove(a[l++]);
        while(cur.r < r) remove(a[r--]);

        res[cur.idx] = curr;
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
