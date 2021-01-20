#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, k;
int g[200001];
int minh[200001], maxh[200001];
bool res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = true;

        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> g[i];
        }

        minh[0] = g[0];
        maxh[0] = g[0];

        for(int i = 1; i < n - 1; i++) {
            minh[i] = g[i];
            if(g[i] + k - 1 < minh[i - 1]) {
                minh[i] = minh[i - 1] + 1 - k;
                if(minh[i] - g[i] > k - 1) {
                    res = false;
                    break;
                }
            }
            if(maxh[i - 1] + k < minh[i] + 1) {
                res = false;
                break;
            }

            maxh[i] = g[i] + k - 1;
            if(maxh[i] > maxh[i - 1] + k - 1) {
                maxh[i] = maxh[i - 1] + k - 1;
            }
            if(minh[i - 1] + 1 > maxh[i] + k) {
                res = false;
                break;
            }
        }
        if(minh[n - 2] + 1 > g[n - 1] + k) res = false;
        if(maxh[n - 2] + k < g[n - 1] + 1) res = false;

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
