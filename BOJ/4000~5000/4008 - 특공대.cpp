#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct CHT
{
    struct Line
    {
        ll a, b; // y = ax + b
    };

    vector<Line> d;

    double cross(const Line& a, const Line& b)
    {
        return (double)(a.b - b.b) / (double)(b.a - a.a);
    }

    void insert(ll a, ll b)
    {
        Line cur = { a, b };
        while(d.size() > 1) {
            Line& b1 = d[d.size() - 1];
            Line& b2 = d[d.size() - 2];
            if(cross(cur, b1) < cross(b1, b2)) {
                d.pop_back();
            } else {
                break;
            }
        }
        d.push_back(cur);
    }

    ll get(ll x)
    {
        int l = 0, r = d.size() - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(cross(d[m], d[m + 1]) <= x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return d[l].a * x + d[l].b;
    }
};

int n;
ll a, b, c, x[1000001];
ll sum[1000001], dp[1000001];
CHT cht;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> a >> b >> c;
    for(int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sum[0] = x[0];
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + x[i];
    }

    dp[0] = x[0] * (x[0] * a + b) + c;
    cht.insert(a * sum[0] * (-2), dp[0] + sum[0] * (sum[0] * a - b));
    for(int i = 1; i < n; ++i) {
        dp[i] = cht.get(sum[i]) + sum[i] * (sum[i] * a + b) + c;
        dp[i] = max(dp[i], sum[i] * (sum[i] * a + b) + c);
        cht.insert(-2 * a * sum[i], dp[i] + sum[i] * (sum[i] * a - b));
    }

    cout << dp[n - 1];

    return 0;
}
