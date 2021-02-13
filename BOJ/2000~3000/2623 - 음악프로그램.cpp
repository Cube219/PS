#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[1001];

int in[1001];

queue<int> q;
vector<int> res;
int pos = true;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        int a;
        cin >> a;
        for(int j = 1; j < num; ++j) {
            int b;
            cin >> b;
            in[b]++;
            g[a].push_back(b);
            a = b;
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(in[i] == 0) q.push(i);
    }

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        res.push_back(cur);

        for(auto nxt : g[cur]) {
            in[nxt]--;
            if(in[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    if(q.empty() == false || res.size() != n) {
        cout << "0";
    } else {
        for(int i = 0; i < n; ++i) {
            cout << res[i] << "\n";
        }
    }

    return 0;
}
