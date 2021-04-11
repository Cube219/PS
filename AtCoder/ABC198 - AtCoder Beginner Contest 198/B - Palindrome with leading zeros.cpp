#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    if(n == 0) cout << "Yes";
    else {
        while(n % 10 == 0) {
            n /= 10;
        }
        while(n > 0) {
            d.push_back(n % 10);
            n /= 10;
        }
        bool res = true;
        int n = d.size();
        for(int i = 0; i < n; ++i) {
            if(d[i] != d[n-i-1]) {
                res = false;
                break;
            }
        }
        if(res == true) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
