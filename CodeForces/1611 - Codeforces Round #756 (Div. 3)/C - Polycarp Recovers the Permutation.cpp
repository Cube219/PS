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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto& v : a) cin >> v;

        if(a[0] != n && a[n - 1] != n) {
            cout << "-1\n";
            continue;
        }

        if(a[0] == n) {
            cout << n << " ";
            for(int i = n - 1; i >= 1; --i) {
                cout << a[i] << " ";
            }
            cout << "\n";
        } else {
            for(int i = n - 2; i >= 0; --i) {
                cout << a[i] << " ";
            }
            cout << n << "\n";
        }
    }

    return 0;
}
