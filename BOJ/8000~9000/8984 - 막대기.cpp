#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Line
{
    int a, b;
    int mod;
    ll len;
};

int n, l;
vector<int> x1, x2;
Line d[100001];
ll dp[100001][2];

int geta(int a)
{
    return lower_bound(x1.begin(), x1.end(), a) - x1.begin();
}
int getb(int b)
{
    return lower_bound(x2.begin(), x2.end(), b) - x2.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b, 0, abs(a - b) + l };
        if(a < b) d[i].mod = -1;
        else if(a == b) d[i].mod = 0;
        else d[i].mod = 1;
        x1.push_back(a);
        x2.push_back(b);
    }
    sort(x1.begin(), x1.end());
    x1.erase(unique(x1.begin(), x1.end()), x1.end());
    sort(x2.begin(), x2.end());
    x2.erase(unique(x2.begin(), x2.end()), x2.end());
    sort(d, d + n, [](const Line& l, const Line& r) {
        if(l.b == r.b) return l.a < r.a;
        return l.b < r.b;
    });
    for(int i = 0; i < n; ++i) {
        d[i].a = geta(d[i].a);
        d[i].b = getb(d[i].b);
    }

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        //if(d[i].mod == 0) {
            ll a = dp[d[i].a][0];
            ll b = dp[d[i].b][1];
            dp[d[i].a][0] = max(a, b + d[i].len);
            dp[d[i].b][1] = max(b, a + d[i].len);
            res = max(res, dp[d[i].a][0]);
            res = max(res, dp[d[i].b][1]);
        //} else if(d[i].mod == -1) {
        //    dp[d[i].b][1] = max(dp[d[i].b][1], dp[d[i].a][0] + d[i].len);
        //    res = max(res, dp[d[i].b][1]);
        //} else {
        //    dp[d[i].a][0] = max(dp[d[i].a][0], dp[d[i].b][1] + d[i].len);
        //   res = max(res, dp[d[i].a][0]);
        //}

    }
    cout << res;

    return 0;
}
