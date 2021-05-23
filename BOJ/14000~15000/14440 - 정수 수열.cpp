#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 100;

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

int x, y, n;
int a0, a1;
Matrix<2> mat;

void print(int v)
{
    if(v < 10) cout << "0" << v;
    else cout << v;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> x >> y >> a0 >> a1 >> n;

    mat.d[0][0] = x;
    mat.d[0][1] = y;
    mat.d[1][0] = 1;
    mat.pow(n - 1);
    if(n == 0) print(a0);
    else if(n == 1) print(a1);
    else {
        ll res = 0;
        res = a1 * mat.d[0][0] + a0 * mat.d[0][1];
        res %= MOD;
        print(res);
    }

    return 0;
}
