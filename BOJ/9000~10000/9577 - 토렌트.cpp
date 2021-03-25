#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[101];
int a[101], b[101];
bool isComp[101];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

int tNum;
int n, m;

void init()
{
    for(int i = 0; i <= 100; ++i) {
        a[i] = -1;
        g[i].clear();
    }
    for(int i = 1; i <= n; ++i) {
        b[i] = -1;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        init();
        for(int i = 0; i < m; ++i) {
            int t1, t2, num;
            cin >> t1 >> t2 >> num;
            for(int j = 0; j < num; ++j) {
                int p;
                cin >> p;
                for(int k = t1; k < t2; ++k) {
                    g[k].push_back(p);
                }
            }
        }

        int cnt = 0;
        int res = -1;
        for(int i = 0; i <= 100; ++i) {
            if(a[i] == -1) {
                for(int j = 1; j <= n; ++j) {
                    isComp[j] = false;
                }
                if(bp(i) == true) cnt++;
            }
            if(cnt == n) {
                res = i + 1;
                break;
            }
        }
        cout << res << "\n";
    }

    return 0;
}
