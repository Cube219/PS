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
int n;

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
        if(n == 1) {
            cout << "0\n";
            continue;
        }
        int cnt = 0;
        if(n % 2 == 1) {
            n--;
            cnt++;
        }
        if(n == 2) cnt++;
        else cnt += 2;
        cout << cnt << "\n";
    }

    return 0;
}
