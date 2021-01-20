#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int v, e;
vector<int> g[10001];

int order[10001];
int orderCnt;
bool isCut[10001];
vector<int> cuts;

int dfs(int node, bool isRoot)
{
    order[node] = ++orderCnt;
    int res = order[node];

    int child = 0;
    for(int next : g[node]) {
        if(order[next] == 0) {
            child++;
            int r = dfs(next, false);
            if(isRoot == false && r >= order[node]) {
                if(isCut[node] == false) cuts.push_back(node);
                isCut[node] = true;
            }
            res = min(res, r);
        } else {
            res = min(res, order[next]);
        }
    }

    if(isRoot == true && child >= 2) {
        if(isCut[node] == false) cuts.push_back(node);
        isCut[node] = true;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    for(int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    for(int i = 1; i <= v; i++) {
        if(order[i] == 0) {
            dfs(i, true);
        }
    }

    sort(cuts.begin(), cuts.end());
    cout << cuts.size() << "\n";
    for(int i = 0; i < cuts.size(); i++) {
        cout << cuts[i] << " ";
    }

    return 0;
}
