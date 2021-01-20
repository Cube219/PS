#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int w[100001], parent[100001];
vector<int> g[100001];
vector<int> d[100001];

ll dNum[100001];
ll num[100001];
ll res;

void calDiv(int x)
{
    if(d[x].size() > 0) return;

    for(int i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            d[x].push_back(i);
            if(i != x / i) {
                d[x].push_back(x / i);
            }
        }
    }
}

void add(int x)
{
    for(int i = 0; i < d[x].size(); i++) {
        dNum[d[x][i]]++;
    }
    num[x]++;
}

void sub(int x)
{
    for(int i = 0; i < d[x].size(); i++) {
        dNum[d[x][i]]--;
    }
    num[x]--;
}

void dfs(int node)
{
    for(int i = 0; i < d[w[node]].size(); i++) {
        if(d[w[node]][i] == w[node]) continue;
        res += num[d[w[node]][i]];
    }
    res += dNum[w[node]];

    add(w[node]);

    for(auto next : g[node]) {
        dfs(next);
    }

    sub(w[node]);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 2; i <= n; i++) {
        cin >> parent[i];
        g[parent[i]].push_back(i);
    }

    for(int i = 1; i <= n; i++) {
        calDiv(w[i]);
    }

    add(w[1]);
    for(auto next : g[1]) {
        dfs(next);
    }

    cout << res;

    return 0;
}
