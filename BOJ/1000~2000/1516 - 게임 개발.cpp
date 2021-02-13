#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n;
vector<int> g[501];
int in[501];
int t[501];
queue<int> q;
int d[501];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> t[i];
        while(1) {
            int a;
            cin >> a;
            if(a == -1) break;
            in[i]++;
            g[a].push_back(i);
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(in[i] == 0) {
            q.push(i);
        }
    }

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        d[cur] += t[cur];

        for(auto nxt : g[cur]) {
            in[nxt]--;
            if(in[nxt] == 0) q.push(nxt);

            d[nxt] = max(d[nxt], d[cur]);
        }
    }

    for(int i = 1; i <= n; ++i) {
        cout << d[i] << "\n";
    }

    return 0;
}
