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
vector<pair<int, ll>> g[101];
int in[101];

queue<int> q;
ll d[101];

bool isBase[101];
ll res[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        in[b]++;
    }

    for(int i = 1; i < n; ++i) {
        if(g[i].size() == 0) isBase[i] = true;
    }

    q.push(n);
    d[n] = 1;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cnt = nx.second;
            d[nxt] += d[cur] * cnt;

            in[nxt]--;
            if(in[nxt] == 0) q.push(nxt);
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(isBase[i] == true) {
            cout << i << " " << d[i] << "\n";
        }
    }

    return 0;
}
