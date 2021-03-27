#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
struct Info
{
    ll id;
    ll x1;
    ll x2;
    // int dis;
};
pair<ll, ll> d[200001];
vector<Info> b;
ll dp[200001][2];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].first >> d[i].second;
    }
    sort(d, d + n, [](const auto& l, const auto& r) {
        return l.second < r.second;
    });
    b.push_back({ d[0].second, d[0].first, d[0].first });
    for(int i = 1; i < n; ++i) {
        if(b.back().id != d[i].second) {
            b.push_back({ d[i].second, d[i].first, d[i].first });
        } else {
            ll x1 = b.back().x1;
            ll x2 = b.back().x2;
            x1 = min(x1, d[i].first);
            x2 = max(x2, d[i].first);
            b.back().x1 = x1;
            b.back().x2 = x2;
        }
    }
    // 0: x1 -> x2
    // 1: x2 -> x1
    dp[0][0] = abs(b[0].x1) + abs(b[0].x1 - b[0].x2);
    dp[0][1] = abs(b[0].x2) + abs(b[0].x1 - b[0].x2);
    for(int i = 1; i < b.size(); ++i) {
        ll l = abs(b[i].x1 - b[i].x2);

        ll aa = dp[i - 1][0] + abs(b[i - 1].x2 - b[i].x1) + l;
        ll bb = dp[i - 1][1] + abs(b[i - 1].x1 - b[i].x1) + l;
        dp[i][0] = min(aa, bb);
        aa = dp[i - 1][0] + abs(b[i - 1].x2 - b[i].x2) + l;
        bb = dp[i - 1][1] + abs(b[i - 1].x1 - b[i].x2) + l;
        dp[i][1] = min(aa, bb);

    }
    int m = b.size();
    ll r1 = abs(b.back().x2) + dp[m - 1][0];
    ll r2 = abs(b.back().x1) + dp[m - 1][1];
    cout << min(r1, r2);

    return 0;
}
