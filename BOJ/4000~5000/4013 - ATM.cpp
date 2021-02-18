#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[500001];
ll money[500001];
bool hasr[500001];
int s, p;
int scc[500001];

int scNum;
vector<int> g2[500001];
int in[500001];
ll m2[500001];
bool r[500001];
ll dp[500001];
bool fromSt[500001];

int d[500001], dNum = 1;
vector<int> st;
bool finish[500001];

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int res = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) res = min(res, dfs(nxt));
        if(finish[nxt] == false) res = min(res, d[nxt]);
    }

    if(res == d[cur]) {
        while(1) {
            int top = st.back();
            st.pop_back();

            scc[top] = scNum;
            m2[scNum] += money[top];
            if(hasr[top] == true) r[scNum] = true;
            finish[top] = true;

            if(top == cur) break;
        }
        scNum++;
    }

    return res;
}

ll process()
{
    ll res = 0;

    queue<int> q;

    for(int i = 0; i < scNum; ++i) {
        dp[i] = m2[i];
        if(in[i] == 0) q.push(i);
    }
    fromSt[scc[s]] = true;
    
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        for(int nxt : g2[cur]) {
            in[nxt]--;
            if(fromSt[cur] == true) {
                if(dp[nxt] < dp[cur] + m2[nxt]) {
                    dp[nxt] = dp[cur] + m2[nxt];
                }
                fromSt[nxt] = true;
            }

            if(in[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    for(int i = 0; i < scNum; ++i) {
        if(fromSt[i] == true && r[i] == true && res < dp[i]) {
            res = dp[i];
        }
    }
    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for(int i = 1; i <= n; ++i) {
        cin >> money[i];
    }
    cin >> s >> p;
    for(int i = 0; i < p; ++i) {
        int a;
        cin >> a;
        hasr[a] = true;
    }

    for(int i = 1; i <= n; ++i) {
        if(finish[i] == false) dfs(i);
    }

    for(int i = 1; i <= n; ++i) {
        for(int j : g[i]) {
            if(scc[i] != scc[j]) {
                in[scc[j]]++;
                g2[scc[i]].push_back(scc[j]);
            }
        }
    }

    cout << process();

    return 0;
}
