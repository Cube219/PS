#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int d[1001];
bool has[11];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    d[1] = 0;
    d[2] = 1;
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j < 10; ++j) {
            has[j] = false;
        }
        for(int j = 0; j < i; ++j) {
            int a = j;
            int b = i - j - 2;
            if(a > b) break;

            int v = d[a] ^ d[b];
            has[v] = true;
        }
        for(int j = 0; j < 10; ++j) {
            if(has[j] == false) {
                d[i] = j;
                break;
            }
        }
    }
    if(d[n] > 0) cout << "1";
    else cout << "2";

    return 0;
}
