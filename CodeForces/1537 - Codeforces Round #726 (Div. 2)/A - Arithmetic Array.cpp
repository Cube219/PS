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
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            sum += a;
        }
        if(sum == n) cout << "0\n";
        else if(sum < n) cout << "1\n";
        else cout << sum - n << "\n";
    }

    return 0;
}
