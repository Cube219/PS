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
ll n;

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
        int cnt = 0;
        ll cur = 2050000000000000000;
        while(n > 0) {
            if(n - cur < 0) {
                cur /= 10;
                if(cur < 2050) break;
                continue;
            }
            n -= cur;
            cnt++;
        }
        if(n != 0) cout << "-1\n";
        else cout << cnt << "\n";
    }

    return 0;
}
