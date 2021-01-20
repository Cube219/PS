#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int n;
vector<int> adj[100001];
int pp[100001];
int sz[100001];

int p(int node, int parent)
{
    sz[node] = 1;
    pp[node] = parent;
    for(auto next: adj[node]) {
        if(next == parent) continue;
        sz[node] += p(next, node);
    }
    return sz[node];
}

int cent(int node, int parent)
{
    for(auto next : adj[node]) {
        if(next == parent) continue;

        if(sz[next] > n / 2) return cent(next, node);
    }
    return node;
}

int getmaxv(int node)
{
    int sum = 0;
    int maxV = -1;
    for(auto ch : adj[node]) {
        if(pp[node] == ch) continue;
        sum += sz[ch];
        if(maxV < sz[ch]) maxV = sz[ch];
    }
    if(maxV < n - 1 - sum) maxV = n - 1 - sum;

    return maxV;
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
            adj[i].clear();
            sz[i] = 0;
        }

        for(int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        p(1, -1);

        int centNode = cent(1, -1);
        int centMaxV = getmaxv(centNode);
        int centNode2 = -1;
        
        for(auto ch : adj[centNode]) {
            int v = getmaxv(ch);
            if(centMaxV == v) {
                centNode2 = ch;
                break;
            }
        }

        if(centNode2 == -1) {
            cout << "1 " << adj[1][0] << "\n";
            cout << "1 " << adj[1][0] << "\n";
        } else {
            int res = -1;
            for(auto ch : adj[centNode]) {
                if(ch == centNode2) continue;
                res = ch;
                break;
            }

            cout << centNode << " " << res << "\n";

            cout << centNode2 << " " << res << "\n";
        }
    }

    return 0;
}
