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
ll a, b;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b;
        if(a > b) swap(a, b);
        ll gap = b - a;
        if(gap == 0) cout << "0 0\n";
        else {
            cout << gap << " ";
            ll cnt = a % gap;
            cnt = min(cnt, gap - cnt);
            cout << cnt;
            cout << "\n";
        }
    }

    return 0;
}
