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
vector<int> gr[101];
queue<int> q;
ll d[101];
bool isInQ[101];
int num[101];
bool hasCycle;
int rec[101];

constexpr ll INF = 999999999;

void search(int node)
{
    num[node] = 0;
    for(auto next : gr[node]) {
        if(num[next] == 0) continue;
        search(next);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        gr[b].push_back(a);
    }

    for(int i = 2; i <= n; i++) {
        d[i] = -INF;
        num[i] = -1;
    }

    search(n);

    q.push(1);
    isInQ[1] = true;
    d[1] = 0;

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        num[cur]++;
        if(num[cur] > n) {
            hasCycle = true;
            break;
        }

        isInQ[cur] = false;

        for(auto n : g[cur]) {
            int next = n.first;
            ll cost = n.second;

            if(num[next] == -1) continue;

            if(d[next] < d[cur] + cost) {
                d[next] = d[cur] + cost;
                rec[next] = cur;

                if(isInQ[next] == false) {
                    isInQ[next] = true;
                    q.push(next);
                }
            }
        }
    }

    if(hasCycle == true) {
        cout << "-1\n";
    } else {
        vector<int> st;
        int cur = n;
        while(cur != 1) {
            st.push_back(cur);
            cur = rec[cur];
        }
        st.push_back(1);

        for(int i = st.size() - 1; i >= 0; i--) {
            cout << st[i] << " ";
        }
    }

    return 0;
}
