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
vector<int> g[100001];
struct Node
{
    ll w;
    int dg;
};
Node node[100001];

ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> node[i].w;
            node[i].dg = 0;

            g[i].clear();
        }
        for(int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
            node[a].dg++;
            node[b].dg++;
        }

        sort(node + 1, node + 1 + n, [](const Node& l, const Node& r) { return l.w > r.w; });
        res = 0;
        for(int i = 1; i <= n; i++) {
            res += node[i].w;
        }

        cout << res << " ";
        int idx = 0;
        for(int i = 0; i < n - 2; i++) {
            while(node[idx].dg <= 1) {
                idx++;
            }
            res += node[idx].w;
            node[idx].dg--;
            cout << res << " ";
        }
        cout << "\n";
    }

    return 0;
}
