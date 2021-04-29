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
int r, b, d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> r >> b >> d;
        int cnt = min(r, b);
        r -= cnt;
        b -= cnt;
        int remain = r + b;

        int tmp;
        if(remain % cnt == 0) {
            tmp = remain / cnt;
        } else {
            tmp = remain / cnt + 1;
        }
        if(tmp <= d) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
