#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;
int n, q, c[300001];
pair<lli, lli> t[1050001];
int stLeaf;

pair<lli, lli> p(int cl, int cr, int l, int r, int node)
{
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return { 0, 0 };

    int m = (cl + cr) / 2;
    auto left = p(cl, m, l, r, node * 2);
    auto right = p(m + 1, cr, l, r, node * 2 + 1);

    return { left.first + right.first, left.second + right.second };
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;

    stLeaf = 1;
    while(stLeaf < n) {
        stLeaf *= 2;
    }

    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            t[stLeaf + i] = { c[i], 0 };
        } else {
            t[stLeaf + i] = { 0, c[i] };
        }
    }

    for(int i = stLeaf - 1; i >= 1; i--) {
        t[i] = { t[i * 2].first + t[i * 2 + 1].first, t[i * 2].second + t[i * 2 + 1].second };
    }

    for(int i = 0; i < q; i++) {
        int a, l, r;
        cin >> a >> l >> r;

        if(a == 1) {
            l--;
            r--;

            auto res = p(0, stLeaf - 1, l, r, 1);
            lli rr = res.first - res.second;
            if(rr < 0) rr = -rr;
            cout << rr << "\n";
        } else {
            l--;

            int node = stLeaf + l;
            while(node > 0) {
                if(l % 2 == 0) {
                    t[node].first += (lli)r;
                } else {
                    t[node].second += (lli)r;
                }
                node /= 2;
            }
        }
    }

    return 0;
}
