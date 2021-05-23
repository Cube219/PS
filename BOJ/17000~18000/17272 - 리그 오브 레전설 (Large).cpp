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
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) d[i][j] = 1;
                else d[i][j] = 0;
            }
        }
    }

    void mulself()
    {
        Matrix tmp;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < n; ++k) {
                    tmp.d[i][j] += (d[i][k] * d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                d[i][j] = tmp.d[i][j];
            }
        }
    }

    void mul(const Matrix& b)
    {
        Matrix tmp;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < n; ++k) {
                    tmp.d[i][j] += (d[i][k] * b.d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                d[i][j] = tmp.d[i][j];
            }
        }
    }

    void pow(ll p)
    {
        Matrix res;
        res.init(n);
        while(p > 0) {
            if(p % 2 == 1) {
                res.mul(*this);
            }
            mulself();
            p /= 2;
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                d[i][j] = res.d[i][j];
            }
        }
    }
};

ll n;
int m;
Matrix<100> mat;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    mat.n = m;
    mat.d[0][0] = 1;
    mat.d[0][m - 1] = 1;
    for(int i = 1; i < m; ++i) {
        mat.d[i][i - 1] = 1;
    }
    if(n - m < 0) {
        cout << "1";
    } else {
        mat.pow(n - m + 1);
        ll res = 0;
        for(int i = 0; i < m; ++i) {
            res += mat.d[0][i];
            res %= MOD;
        }
        cout << res;
    }

    return 0;
}
