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
ll n, m, d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m >> d;
        ll r1 = (n - 1) + n * (m - 1);
        ll r2 = (m - 1) + m * (n - 1);
        if(r1 > r2) swap(r1, r2);
        if(r1 <= d && d <= r2) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
