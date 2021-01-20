#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
struct Node
{
    int x;
    int width;
};
bool operator<(const Node& l, const Node& r)
{
    return l.x < r.x;
}
Node d[10001];
int dp[10001];

int p(int st)
{
    dp[st] = 987654321;

    int pos = d[st].x;
    int cnt = 0;
    for(int i = st + 1; i < n; i++) {
        int boxLeft = d[i].x - d[i].width;

        if(pos == boxLeft) {
            dp[st] = min(dp[st], cnt + dp[i]);
            return dp[st];
        } else if(pos < boxLeft) {
            dp[st] = min(dp[st], cnt + dp[i]);
            pos += d[i].width;
            if(pos < d[i].x) {
                cnt++;
            }
        } else {
            pos += d[i].width;
            if(pos - d[i].width > d[i].x) {
                cnt++;
            }
        }
    }

    dp[st] = min(dp[st], cnt);

    return dp[st];
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i].x;
    }
    for(int i = 0; i < n; i++) {
        cin >> d[i].width;
    }

    sort(d, d + n);

    for(int i = n - 1; i >= 0; i--) {
        p(i);
    }

    int res = 987654321;
    for(int i = 0; i < n; i++) {
        if(res > i + dp[i]) res = i + dp[i];
    }

    cout << res;

    return 0;
}
