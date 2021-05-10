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
int res[2501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) res[i] = 3;
        else res[i] = 5;
    }
    res[0] *= 5 * 659;
    for(int i = 1; i < n; ++i) {
        res[i] *= 2;
    }

    int cura = 2, curb = 2, curc = 1;
    for(int i = 3; i < n; i++) {
        if(i % 2 == 1) {
            res[i] *= cura;
            if(res[i] > 10000) {
                res[i] /= cura;
                res[i] /= 2;
                res[i] *= 3;
                res[i] *= curc;
                curc += 2;
                while(curc % 659 == 0) curc += 2;
            }
            cura++;
            while(cura % 659 == 0) cura++;
        } else {
            res[i] *= curb;
            curb++;
            while(curb % 659 == 0 || curb % 5 == 0) curb++;
        }
    }
    for(int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
