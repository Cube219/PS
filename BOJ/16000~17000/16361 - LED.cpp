#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    ll v, l;
};

int n;
Node d[300001];

bool ck(ll k)
{
    int st = 0;
    if(d[0].v == 0) {
        st = 1;
        if(k < d[0].l) return false;
    }

    int i;
    for(i = st; i < n; ++i) {
        if(k < d[i].l) break;
    }
    if(i >= n) return true;

    ll up = d[i].l + k;
    ll down = max(0LL, d[i].l - k);
    i++;
    ll lastdown = down;
    for(; i < n; ++i) {
        up = min(up, d[i].l + k);
        down = max(down, d[i].l - k);
        if(up < down) break;
        lastdown = down;
    }
    if(i >= n) return true;

    up = d[i].l + k;
    down = max(lastdown, d[i].l - k);
    if(up < down) return false;
    i++;
    for(; i < n; ++i) {
        up = min(up, d[i].l + k);
        down = max(down, d[i].l - k);
        if(up < down) break;
    }
    if(i >= n) return true;

    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].v >> d[i].l;
        d[i].l *= 2;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.v < r.v;
    });

    ll l = -1, r = 2000001000;
    while(l + 1 < r) {
        ll m = (l + r) / 2;
        if(ck(m)) {
            r = m;
        } else {
            l = m;
        }
    }

    if(r % 2 == 0) cout << r / 2 << ".0";
    else cout << r / 2 << ".5";

    return 0;
}
