#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

const ll MOD = 998244353;

int tNum;
int n, k;
int l[200002], r[200002];
int a[200002], b[200002];
bool used[200002];

ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            l[a[i]] = 0;
            r[a[i]] = 0;
        }

        l[a[0]] = -1;
        r[a[0]] = a[1];
        for(int i = 1; i < n - 1; i++) {
            l[a[i]] = a[i - 1];
            r[a[i]] = a[i + 1];
        }
        l[a[n - 1]] = a[n - 2];
        r[a[n - 1]] = -1;

        res = 1;
        for(int i = 0; i < k; i++) {
            cin >> b[i];
            used[b[i]] = true;
        }
        for(int i = 0; i < k; i++) {
            used[b[i]] = false;

            int cnt = 0;
            int lv = l[b[i]];
            int rv = r[b[i]];
            if(lv != -1 && used[lv] == false) {
                cnt++;
            }
            if(rv != -1 && used[rv] == false) {
                cnt++;
            }

            res = (res * cnt) % MOD;
        }

        cout << res << "\n";
    }

    return 0;
}
