#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
vector<int> g[200001];
vector<int> cnt[200001];

int p(int node, int parent)
{
    int r = 0;

    for(int i = 0; i < g[node].size(); i++) {
        int next = g[node][i];
        if(next == parent) {
            cnt[node][i] = 0;
            continue;
        }

        cnt[node][i] = p(next, node);
    }
    sort(cnt[node].begin(), cnt[node].end());
    for(int i = 0; i < cnt[node].size(); i++) {
        int c = cnt[node][i];
        if(c == 0) continue;
        if(r < c + 1) {
            r = c + 1;
        }
    }

    return r;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            g[i].clear();
            cnt[i].clear();
        }
        for(int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
            cnt[a].push_back(0);
            cnt[b].push_back(0);
        }

        cout << p(1, -1) - 1 << "\n";
    }

    return 0;
}
