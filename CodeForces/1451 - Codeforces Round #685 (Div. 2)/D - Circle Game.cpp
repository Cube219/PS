#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

int tNum;
int d, k;
int b[100001];
bool dp[110001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> d >> k;

        /*bool res = false;
        int cnt = d / k;
        if(cnt % 2 == 0) res = false;
        else res = true;*/

        ll d2 = (ll)d * d;
        int st = 0;
        int num = 0;
        for(int i = 0; i <= d; i += k) {
            ll i2 = (ll) i * i;
            ll remain = sqrt(d2 - i2);
            b[num] = remain / k;
            num++;
        }
        bool res = true;
        int cnt = 0;
        for(int i = 0; i < num; ++i) {
            if(b[i] == i) {
                res = false;
                break;
            }
        }

        if(res == true) cout << "Ashish\n";
        else cout << "Utkarsh\n";
    }

    return 0;
}
