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
bool isf[5001], tmp[5001], flipped[5001];

int process(int k)
{
    for(int i = 0; i < n; ++i) {
        tmp[i] = isf[i];
        flipped[i] = false;
    }
    int res = 0;
    int num = 0;
    for(int i = 0; i <= n - k; ++i) {
        if(num % 2 == 1) tmp[i] = !tmp[i];
        if(tmp[i] == false) {
            res++;
            tmp[i] = true;
            flipped[i] = true;
            num++;
        }
        if(i - k + 1 >= 0 && flipped[i - k + 1] == true) num--;
    }
    for(int i = n - k + 1; i < n; ++i) {
        if(num % 2 == 1) tmp[i] = !tmp[i];
        if(i - k + 1 >= 0 && flipped[i - k + 1] == true) num--;
    }
    for(int i = 0; i < n; ++i) {
        if(tmp[i] == false) return -1;
    }
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        if(ch == 'F') isf[i] = true;
    }

    int res = n + 1, k = 0;
    for(int i = 1; i <= n; ++i) {
        int r = process(i);

        if(r == -1) continue;
        if(res > r) {
            res = r;
            k = i;
        }
    }

    cout << k << " " << res;

    return 0;
}
