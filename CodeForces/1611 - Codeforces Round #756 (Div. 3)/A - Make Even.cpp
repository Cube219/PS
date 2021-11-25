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
        vector<int> d;
        while(n>0) {
            d.push_back(n % 10);
            n /= 10;
        }
        if(d[0] % 2 == 0) {
            cout << "0\n";
            continue;
        }
        if(d.back() % 2 == 0) {
            cout << "1\n";
            continue;
        }
        bool even = false;
        for(int v : d) {
            if(v%2 == 0) {
                even = true;
                break;
            }
        }
        if(even == true) {
            cout << "2\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
