#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, p[10001], r[10001], w[10001], vn;
bool v[10001];
vector<int> edges[10001];
queue<int> q;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        int m;
        cin >> m;
        for(int j = 0; j < m; j++) {
            int a;
            cin >> a;
            edges[i].push_back(a);
        }
    }

    for(int i = 1; i <= n; i++) {
        vector<int>& es = edges[i];
        for(int j = 0; j < es.size(); j++) {
            r[es[j]]++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(r[i] == 0) {
            q.push(i);
        }
    }

    while(q.empty() == false) {
        int current = q.front();
        q.pop();

        int myTime = w[current] + p[current];
        if(res < myTime) {
            res = myTime;
        }

        v[current] = true;
        vn++;

        for(auto next : edges[current]) {
            if(v[next] == true) continue;

            r[next]--;
            if(w[next] < myTime) {
                w[next] = myTime;
            }

            if(r[next] == 0) {
                q.push(next);
            }
        }
    }

    if(vn != n) res = -1;

    cout << res;

    return 0;
}
