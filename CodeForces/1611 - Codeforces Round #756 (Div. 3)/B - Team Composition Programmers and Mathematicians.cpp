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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        int res = 0;

        int gap = b - a;
        int cnt = gap / 2;
        cnt = min(cnt, a);
        res += cnt;
        a -= cnt;
        b -= cnt * 3;
        res += min(a, b) / 2;
        cout << res << "\n";
    }

    return 0;
}
