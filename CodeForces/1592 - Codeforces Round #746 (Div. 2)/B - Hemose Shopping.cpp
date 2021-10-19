#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, x;
int d[100001], d2[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> x;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            d2[i] = d[i];
        }
        sort(d, d + n);

        if(n >= x * 2) {
            cout << "YES\n";
            continue;
        }

        int l = n - x;
        bool res = true;
        for(int i = min(x - 1, n - 1); i >= l && i >= 0; --i) {
            if(d[i] != d2[i]) {
                res = false;
                break;
            }
        }
        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
