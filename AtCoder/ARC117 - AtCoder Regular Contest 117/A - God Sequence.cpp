#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int a, b;
vector<int> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b;

    int cur = 1000000000;
    while(a > 1 && b > 1) {
        res.push_back(-cur);
        res.push_back(cur);
        a--; b--;
        cur--;
    }
    if(a == 1) {
        int sum = 0;
        for(int i = 1; i <= b; ++i) {
            res.push_back(-i);
            sum += i;
        }
        res.push_back(sum);
    } else {
        int sum = 0;
        for(int i = 1; i <= a; ++i) {
            res.push_back(i);
            sum -= i;
        }
        res.push_back(sum);
    }

    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
