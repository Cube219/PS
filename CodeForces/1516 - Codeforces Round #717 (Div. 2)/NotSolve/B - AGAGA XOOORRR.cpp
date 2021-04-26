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
int d[2001];

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
            cin >> d[i];
        }
        bool res = false;

        for(int i = 0; i < n; ++i) {
            int m = d[i];
            int l = 0, r = 0;
            if(i > 0) {
                for(int j = 0; j <= i - 1; ++j) {
                    l ^= d[j];
                }
            }
            if(i < n - 1) {
                for(int j = i + 1; j < n; ++j) {
                    r ^= d[j];
                }
            }
            if(l == m && m == r) {
                res = true;
                break;
            } else if((l ^ m) == r) {
                res = true;
                break;
            } else if(l == (m ^ r)) {
                res = true;
                break;
            }
        }

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
