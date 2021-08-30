#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector<char> res;
    while(n > 1) {
        if((n & 1) > 0) res.push_back('A');
        n /= 2;
        res.push_back('B');
    }
    cout << 'A';
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }

    return 0;
}
