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
        int o = 0, e = 0;
        for(int i = 0; i < n * 2; ++i) {
            int a;
            cin >> a;
            if(a % 2 == 1) o++;
            else e++;
        }
        if(o == n && e == n) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
