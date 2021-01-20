#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
int k[300001];
ll c[300001];

ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        cin >> n >> m;
        for(int i = 0; i < n; i++) cin >> k[i];
        for(int i = 1; i <= m; i++) cin >> c[i];
        sort(k, k + n);

        int idx = 1;
        for(int i = n-1; i >= 0; i--) {
            if(idx <= k[i]) {
                res += c[idx];
                idx++;
            } else {
                res += c[k[i]];
            }
        }

        cout << res << "\n";
    }

    return 0;
}
