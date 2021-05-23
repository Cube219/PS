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

template <int N>
struct Matrix
{
    ll d[N][N];

    void init()
    {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(i == j) d[i][j] = 1;
                else d[i][j] = 0;
            }
        }
    }

    void mulself()
    {
        Matrix tmp;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < N; ++k) {
                    tmp.d[i][j] += (d[i][k] * d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                d[i][j] = tmp.d[i][j];
            }
        }
    }

    void mul(const Matrix& b)
    {
        Matrix tmp;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < N; ++k) {
                    tmp.d[i][j] += (d[i][k] * b.d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                d[i][j] = tmp.d[i][j];
            }
        }
    }

    void pow(ll p)
    {
        Matrix res;
        res.init();
        while(p > 0) {
            if(p % 2 == 1) {
                res.mul(*this);
            }
            mulself();
            p /= 2;
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                d[i][j] = res.d[i][j];
            }
        }
    }
};

int k;
ll n;
Matrix<52> m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k >> n;
    for(int i = 0; i <= k + 1; ++i) {
        for(int j = 0; j <= i; ++j) {
            m.d[i][j] = 1;
        }
    }
    m.pow(n - 1);
    if(n == 1) cout << "1";
    else {
        ll res = 0;
        for(int i = 0; i <= k + 1; ++i) {
            res += m.d[k + 1][i];
            res %= MOD;
        }
        cout << res;
    }

    return 0;
}
