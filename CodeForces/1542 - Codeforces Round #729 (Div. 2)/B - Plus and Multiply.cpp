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
ll n, a, b;
bool res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> a >> b;
        bool res = false;

        if(a == 1) {
            if((n - 1) % b == 0) res = true;
        } else {
            ll cur = 1;
            while(cur <= n) {
                if((n - cur) % b == 0) {
                    res = true;
                    break;
                }
                cur *= a;
            }
        }
        if(n == 1) res = true;
        
        if(res == true) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
