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
int n, k;
int res;

int main(void)
{
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        int mask = 0;
        for(int i = 0; i < n; ++i) {
            cout << (mask ^ i) << endl;
            cin >> res;
            if(res == 1) break;
            mask ^= (mask ^ i);
        }
    }

    return 0;
}
