#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

using ll = long long int;
constexpr ll INF = 99999999999999999;

ll n, k;
ll lc, pc, lm, pm, pt, mt;
ll l[100001];
ll res = INF;

// +: 잉여 값, -: 요구 값
ll ap(ll v, ll target)
{
    ll gap = min(mt, abs(v - target));
    if(v - target < 0) gap *= -1;

    return gap;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    cin >> lc >> pc >> lm >> pm;
    cin >> pt >> mt;
    for(int i = 0; i < n; ++i) {
        cin >> l[i];
    }

    sort(l, l + n);

    ll surpl = 0, usel = 0;
    res = INF;
    bool pos = true;
    ll curv = 0;
    int lastl = -1;
    for(int i = n - 1; i >= 0; --i) {
        ll gap = ap(l[i], lm);
        if(gap >= 0) {
            surpl += gap;
        } else {
            gap *= -1;
            usel += gap;
            surpl -= gap;
            if(surpl < 0 || gap + l[i] < lm) {
                pos = false;
                if(lastl == -1) lastl = i;
            }
        }
        curv += pm;
    }
    curv += usel * pt;
    if(pos == true) res = curv;

    int right = n - 1;
    int left = 0;
    while(left < right) {
        for(int i = 0; i < k - 1; ++i) {
            ll gap = ap(l[left], lm);
            if(gap < 0) {
                gap *= -1;
                usel -= gap;
                surpl += gap;
                curv -= gap * pt;
            }
            curv -= pm;

            gap = ap(l[left], 1);
            if(gap > 0) surpl += gap;
            left++;
            if(left == right) break;
        }

        ll gap = ap(l[right], lm);
        if(gap >= 0) {
            surpl += gap;
        } else {
            gap *= -1;
            usel -= gap;
            surpl += gap;
            curv -= gap * pt;
        }

        gap = ap(l[right], lc);
        if(gap >= 0) {
            surpl += gap;
        } else {
            gap *= -1;
            usel += gap;
            surpl -= gap;
            curv += gap * pt;
            if(gap + l[right] < lc) {
                break;
            }
        }

        curv -= pm;
        curv += pc;

        if(surpl >= 0 && (left - 1 >= lastl || lastl >= right)) {
            res = min(res, curv);
        }
        right--;
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
