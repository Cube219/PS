#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int g, k, l;
int n, m;
string s, t;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> g >> k >> l;
    for(int i = 0; i < g; ++i) {
        cin >> n >> s;
        cin >> m >> t;
        if(n == m || k == 1) cout << "YS\n";
        else if(n < m) cout << "Y\n";
        else cout << "S\n";
    }

    return 0;
}
