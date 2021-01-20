#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int d, t;

lli m1[51][51], m2[51][51], tmp[51][51], c[51];
vector<int> bit;

constexpr lli MOD = 31991;

void mul1()
{
    for(int i = 1; i <= d; i++) {
        for(int j = 1; j <= d; j++) {
            tmp[i][j] = 0;
            for(int k = 1; k <= d; k++) {
                tmp[i][j] = (tmp[i][j] + m1[i][k] * m1[k][j]) % MOD;
            }
        }
    }

    for(int i = 1; i <= d; i++) {
        for(int j = 1; j <= d; j++) {
            m1[i][j] = tmp[i][j];
        }
    }
}

void mul2()
{
    for(int i = 1; i <= d; i++) {
        for(int j = 1; j <= d; j++) {
            tmp[i][j] = 0;
            for(int k = 1; k <= d; k++) {
                tmp[i][j] = (tmp[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
        }
    }

    for(int i = 1; i <= d; i++) {
        for(int j = 1; j <= d; j++) {
            m1[i][j] = tmp[i][j];
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> d >> t;
    c[0] = c[1] = 1;

    lli sum = 2;
    for(int i = 2; i <= d; i++) {
        c[i] = sum;
        sum = (sum + c[i]) % MOD;
    }

    lli res = 0;
    if(t <= d) {
        res = c[t];
    } else {

        for(int i = 1; i <= d; i++) {
            m1[d][i] = 1;
            m2[d][i] = 1;
        }
        for(int i = 1; i < d; i++) {
            m1[i][i + 1] = 1;
            m2[i][i + 1] = 1;
        }

        int pow = t - d;
        while(pow > 0) {
            bit.push_back(pow & 1);
            pow >>= 1;
        }
        bit.pop_back();
        int ck = 1;
        while(bit.empty() == false) {
            mul1();
            ck *= 2;
            if(bit.back() == 1) {
                mul2();
                ck++;
            }
            pow = pow >> 1;

            bit.pop_back();
        }

        for(int i = 1; i <= d; i++) {
            res = (res + m1[d][i] * c[i]) % MOD;
        }
    }

    cout << res;

    return 0;
}
