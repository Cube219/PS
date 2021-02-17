#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[1001];
int d[1001][1001];
int dNum[1001];
ll eNum;
bool visit[1001];

vector<int> res;

void dfs(int cur)
{
    visit[cur] = true;
    for(int nxt : g[cur]) {
        if(d[cur][nxt] >= 1 && dNum[nxt] > 0) {
            d[cur][nxt]--;
            d[nxt][cur]--;
            dNum[nxt]--;
            dNum[cur]--;
            dfs(nxt);
        }
    }
    res.push_back(cur);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int a;
            cin >> a;
            d[i][j] = a;
            if(i > j && a >= 1) {
                g[i].push_back(j);
                g[j].push_back(i);
                eNum += a;
                dNum[i] += a;
                dNum[j] += a;
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(visit[i] == false) {
            res.clear();

            dfs(i);
            if(res.size() > 1) break;
        }
    }

    if(res.size() == eNum + 1 && res.front() == res.back()) {
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
    } else {
        cout << "-1";
    }

    return 0;
}
