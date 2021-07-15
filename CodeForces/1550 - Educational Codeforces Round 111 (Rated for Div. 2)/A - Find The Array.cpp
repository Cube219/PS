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
int s;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> s;
        int sum = 0;
        int cnt = 0;
        int cur = 1;
        while(sum + cur <= s) {
            sum += cur;
            cnt++;
            cur += 2;
        }
        if(sum != s) cnt++;
        cout << cnt << "\n";
    }

    return 0;
}
