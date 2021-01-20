#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
ll dp[5002][5002];

constexpr ll MOD = 1000000007;
int g[5002];

int find(int a)
{
    vector<int> st;
    while(g[a] != a) {
        st.push_back(a);
        a = g[a];
    }

    for(int i = 0; i < st.size(); i++) {
        g[st[i]] = a;
    }

    return a;
}

bool uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);

    if(ar == br) return false;
    g[br] = ar;

    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j >= 2; j--) {
            dp[i][j] = (dp[i - 1][j] * j) % MOD;
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            dp[i][0] = (dp[i][0] + dp[i][j]) % MOD;
        }
        dp[i][1] = 1;
        dp[i][0] = (dp[i][0] + 1) % MOD;
        g[i] = i;
    }
    
    int gNum = n;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        if(uni(a, b) == true) {
            gNum--;
        }
        cout << dp[gNum][0] << "\n";
    }

    return 0;
}
