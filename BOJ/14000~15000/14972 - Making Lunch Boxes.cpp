#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
int d[501][501];
int dp[2][1 << 16];
int cur[501];
int res;
map<vector<int>, int> mp;

void p1(int idx, int cnt)
{
    if(idx == n / 2) {
        vector<int> key(m);
        for(int i = 0; i < m; ++i) {
            key[i] = cur[i];
        }
        auto it = mp.find(key);
        if(it == mp.end()) {
            it = mp.insert({ key, 0 }).first;
        }
        it->second = max(it->second, cnt);
        return;
    }

    p1(idx + 1, cnt);
    for(int j = 0; j < m; ++j) {
        cur[j] += d[idx][j];
        cur[j] %= 2;
    }
    p1(idx + 1, cnt + 1);
    for(int j = 0; j < m; ++j) {
        cur[j] += d[idx][j];
        cur[j] %= 2;
    }
}
void p12(int idx, int cnt)
{
    if(idx == n / 2 - 1) {
        vector<int> key(m);
        for(int i = 0; i < m; ++i) {
            key[i] = cur[i];
        }
        auto it = mp.find(key);
        if(it != mp.end()) {
            res = max(res, cnt + it->second);
        }
        return;
    }

    p12(idx - 1, cnt);
    for(int j = 0; j < m; ++j) {
        cur[j] += d[idx][j];
        cur[j] %= 2;
    }
    p12(idx - 1, cnt + 1);
    for(int j = 0; j < m; ++j) {
        cur[j] += d[idx][j];
        cur[j] %= 2;
    }
}

int p2()
{
    for(int i = 0; i < 1 << m; ++i) {
        dp[0][i] = -1;
        dp[1][i] = -1;
    }
    dp[1][0] = 0;
    dp[0][0] = 0;

    for(int i = 0; i < n; ++i) {
        int v = 0;
        for(int j = 0; j < m; ++j) {
            v *= 2;
            v += d[i][j];
        }
        int cur = i % 2;
        int pre = 1 - cur;
        for(int j = 0; j < 1 << m; ++j) {
            dp[cur][j] = dp[pre][j];
        }
        for(int j = 0; j < 1 << m; ++j) {
            if(dp[pre][j] == -1) continue;
            dp[cur][j ^ v] = max(dp[cur][j ^ v], dp[pre][j] + 1);
        }
    }
    return dp[(n - 1) % 2][0];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> m;
        if(n == 0) break;

        for(int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            for(int j = 0; j < m; ++j) {
                d[i][j] = str[j] - '0';
            }
        }
        if(n <= 31) {
            res = 0;
            mp.clear();
            vector<int> kk(m, 0);
            mp.insert({ kk, 0 });
            p1(0, 0);
            p12(n - 1, 0);
            cout << res << "\n";
        } else {
            cout << p2() << "\n";
        }
    }

    return 0;
}
