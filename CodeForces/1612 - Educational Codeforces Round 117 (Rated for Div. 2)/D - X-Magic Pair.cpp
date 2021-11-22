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
        ll a, b, x;
        cin >> a >> b >> x;
        if(a < b) swap(a, b);

        bool res = false;
        if(x == a || x == b) {
            res = true;
        }
        while(a != b && a>0 && b>0) {
            ll cnt = a / b;
            ll next = a % b;

            if((x - next) % b == 0 && (x - next) / b <= cnt) {
                res = true;
                break;
            }
            a = next;
            if(a < b) swap(a, b);
        }

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
