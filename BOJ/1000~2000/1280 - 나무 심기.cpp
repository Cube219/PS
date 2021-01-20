#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

constexpr lli MOD = 1000000007;

int n, x[200001];
pair<lli, int> t[600001];
int leafStart;
lli res;
int maxX;

pair<lli, int> p(int cl, int cr, int l, int r, int node)
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

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
        if(maxX < x[i]) maxX = x[i];
    }

    leafStart = 1;
    while(leafStart < maxX + 1) {
        leafStart *= 2;
    }

    {
        int node = leafStart + x[0];
        while(node > 0) {
            t[node].second++;
            t[node].first += (lli)x[0];
            node /= 2;
        }
    }

    res = 1;
    for(int i = 1; i < n; i++) {
        auto left = p(0, leafStart - 1, 0, x[i] - 1, 1);
        auto right = p(0, leafStart - 1, x[i] + 1, maxX, 1);

        lli leftValue = ((lli)x[i] * (lli)left.second) - left.first;
        lli rightValue = right.first - ((lli)x[i] * (lli)right.second);
        lli sum = (leftValue + rightValue) % MOD;
        res = (res * sum) % MOD;

        int node = leafStart + x[i];
        while(node > 0) {
            t[node].second++;
            t[node].first += (lli)x[i];
            node /= 2;
        }
    }

    cout << res;

    return 0;
}
