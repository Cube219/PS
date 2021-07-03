#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
ll x, y;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> y >> x;
        if(n == 0) break;
        x--;
        y = (1LL << n) - y;

        vector<bool> isflip;
        ll tmp = y;
        for(int i = n; i >= 1; --i) {
            ll bit = (1LL << i) - 1;
            if((tmp & (1LL << (i - 1))) > 0) {
                isflip.push_back(true);
                tmp ^= bit;
            } else {
                isflip.push_back(false);
            }
        }
        reverse(isflip.begin(), isflip.end());
        bool isrev = false;
        ll sz = 1LL << n;
        for(int i = 0; i < n; ++i) {
            bool isl = false;
            if(x < sz / 2) {
                isl = true;
            } else {
                isl = false;
                x -= sz / 2;
            }

            if(isrev == true) isl = !isl;
            if(isflip[i] == false) isl = !isl;

            if(isl == true) cout << "L";
            else cout << "R";

            if(isflip[i] == true) {
                isrev = !isrev;
            }
            sz /= 2;
        }
        cout << "\n";
    }

    return 0;
}
