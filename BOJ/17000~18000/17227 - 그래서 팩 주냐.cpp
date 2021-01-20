#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, e;
vector<int> g[100001];
vector<int> st;
int d[100001][2];
queue<int> q;
bool isVisited[100001];
int remainCnt[100001];
int oneNum[100001][2];
vector<int> costs[100001][2];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> e;
    for(int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        g[b].push_back(a);
        remainCnt[a]++;
    }
    for(int i = 1; i <= n; i++) {
        if(g[i].size() == 0) {
            st.push_back(i);
        }
    }

    q.push(n);
    d[n][0] = 999999;
    d[n][1] = 0;

    while(q.empty() == false) {
        int current = q.front();
        q.pop();

        isVisited[current] = true;

        if(current != n) {
            sort(costs[current][0].begin(), costs[current][0].end());
            sort(costs[current][1].begin(), costs[current][1].end());
            d[current][0] = *costs[current][0].begin();
            d[current][1] = *costs[current][1].rbegin();
            int tmp = 0;
            for(int i = costs[current][1].size() - 2; i >= 0; i--) {
                tmp++;
                int newCost = tmp + costs[current][1][i];
                if(d[current][1] > newCost) d[current][1] = newCost;
            }
        }

        for(auto next : g[current]) {
            if(isVisited[next] == true) continue;

            costs[next][0].push_back(d[current][1]);
            costs[next][1].push_back(d[current][0]);

            remainCnt[next]--;
            if(remainCnt[next] == 0) {
                q.push(next);
            }
        }
    }

    int res = 987654321;
    for(int i = 0; i < st.size(); i++) {
        if(res > d[st[i]][1]) {
            res = d[st[i]][1];
        }
    }
    if(res == 999999) res = -1;
    cout << res;

    return 0;
}
