#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;

ll n, q;
ll lk[70][10011], sz[70], cnt[70][10011];
bool isodd[70];

void init(ll curn, int level)
{
    if(curn % 2 == 1) isodd[level] = true;
    if(curn == 1) {
        sz[level] = 1;
        for(int i = 0; i <= 10000; ++i) {
            lk[level][0] = 1;
            cnt[level][i] = 1;
        }
        return;
    }

    init(curn / 2, level + 1);

    sz[level] = sz[level + 1] * 2 + 1;
    int idx = 0;
    while(lk[level + 1][idx] < sz[level + 1] && idx <= 10000) {
        lk[level][idx] = lk[level + 1][idx];
        idx++;
    }
    lk[level][idx] = lk[level + 1][idx];
    if(curn % 2 == 0) {
        idx++;
    }

    for(int i = 0; i <= 10000 && idx <= 10000; ++i) {
        lk[level][idx] = sz[level + 1] + lk[level + 1][i] + 1;
        idx++;
        if(lk[level][idx - 1] == sz[level]) {
            break;
        }
        assert(lk[level][idx - 1] < sz[level]);
    }
    while(idx <= 10000) {
        lk[level][idx] = lk[level][idx - 1];
        idx++;
    }

    // cnt배열 채우기
    int st;
    if(curn % 2 == 1) {
        cnt[level][0] = lk[level + 1][0] * 2 + 1;
        st = 1;
    } else {
        cnt[level][1] = lk[level + 1][0] * 2 + 1;
        st = 2;
    }
    int l = 0, r = 0;
    for(int i = st; i <= 10000; ++i) {
        cnt[level][i] = cnt[level][i - 1];
        if(lk[level + 1][l + 1] + lk[level + 1][r] > lk[level + 1][l] + lk[level + 1][r + 1]) {
            l++;
        } else {
            r++;
        }
        cnt[level][i] = max(cnt[level][i], lk[level + 1][l] + lk[level + 1][r] + 1);
    }
    for(int i = 0; i <= 10000; ++i) {
        cnt[level][i] = max(cnt[level][i], lk[level][i]);
        cnt[level][i] = max(cnt[level][i], cnt[level + 1][i]);
    }
}

ll p(ll cl, ll cr, ll l, ll r, int level, ll k)
{
    if(cr < l || r < cl) return 0;
    if(l <= cl && cr <= r) {
        return cnt[level][k];
    }

    ll ret = 0;
    ll m = (cl + cr) / 2;
    ret = max(ret, p(cl, m - 1, l, r, level + 1, k));
    ret = max(ret, p(m + 1, cr, l, r, level + 1, k));
    if(l <= m && m <= r) {
        ll res = 0;
        ll lmax = m - l;
        ll rmax = r - m;
        if(isodd[level] == false) k--;
        for(int i = 0; i <= k; ++i) {
            ll tmp = 0;
            tmp += min(lmax, lk[level + 1][i]);
            tmp += min(rmax, lk[level + 1][k - i]);
            tmp++;
            res = max(res, tmp);
        }
        ret = max(ret, res);
    }

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    init(n, 0);

    for(int i = 0; i < q; ++i) {
        ll a, b, k;
        cin >> a >> b >> k;
        a--; b--;

        cout << p(0, sz[0] - 1, a, b, 0, k) << "\n";
    }

    return 0;
}
