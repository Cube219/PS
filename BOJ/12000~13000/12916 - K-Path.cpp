#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, k;
ll d[101][101], res[101][101], tmp[101][101];

void mul1()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            tmp[i][j] = 0;
            for(int z = 0; z < n; ++z) {
                tmp[i][j] += d[i][z] * d[z][j];
                tmp[i][j] %= MOD;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            d[i][j] = tmp[i][j];
        }
    }
}

void mul2()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            tmp[i][j] = 0;
            for(int z = 0; z < n; ++z) {
                tmp[i][j] += res[i][z] * d[z][j];
                tmp[i][j] %= MOD;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            res[i][j] = tmp[i][j];
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> d[i][j];
        }
        res[i][i] = 1;
    }

    while(k > 0) {
        if(k % 2 == 1) mul2();
        mul1();
        k /= 2;
    }

    ll r = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            r += res[i][j];
            r %= MOD;
        }
    }

    cout << r;


    return 0;
}
