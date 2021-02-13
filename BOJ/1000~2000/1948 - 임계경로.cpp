#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, m, st, ed;
vector<pair<int, ll>> g[10001];
int in[10001];
ll d[100001];
int cnt;

bool visit[100001];
vector<int> ret[100001];
queue<int> q;

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
    cin >> st >> ed;

    q.push(st);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        if(cur == ed) break;

        for(auto& nx : g[cur]) {
            int next = nx.first;
            ll cost = nx.second;

            if(d[next] < d[cur] + cost) {
                d[next] = d[cur] + cost;
                ret[next].clear();
                ret[next].push_back(cur);
            } else if(d[next] == d[cur] + cost) {
                ret[next].push_back(cur);
            }

            in[next]--;
            if(in[next] == 0) {
                q.push( next );
            }
        }
    }

    q.push(ed);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;

        for(auto next : ret[cur]) {
            cnt++;
            q.push(next);
        }
    }

    cout << d[ed] << "\n";
    cout << cnt << "\n";

    return 0;
}
