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
int n, a[100005];

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
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        bool res = true;
        for(int i = 0; i < n; ++i) {
            bool pos = false;
            for(int j = i; j >= 0; --j) {
                if(a[i] % (j + 2) != 0) {
                    pos = true;
                    break;
                }
            }
            if(pos == false) {
                res = false;
                break;
            }
        }

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
