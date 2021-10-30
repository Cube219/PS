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
int n, a[100005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        if(n % 2 == 0) {
            cout << "YES\n";
            continue;
        }

        bool res = false;
        for(int i = 0; i < n - 1; ++i) {
            if(a[i] >= a[i + 1]) {
                res = true;
                break;
            }
        }
        if(res == false) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
