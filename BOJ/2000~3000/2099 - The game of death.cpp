#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
struct Matrix
{
    bool d[N][N];
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) d[i][j] = true;
                else d[i][j] = false;
            }
        }
    }

    void mulself()
    {
        Matrix tmp;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp.d[i][j] = false;
                for(int k = 0; k < n; ++k) {
                    if(d[i][k] == true && d[k][j] == true) tmp.d[i][j] = true;
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
                tmp.d[i][j] = false;
                for(int k = 0; k < n; ++k) {
                    if(d[i][k] == true && b.d[k][j] == true) tmp.d[i][j] = true;
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


int n, k, m;
Matrix<200> mat;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> m;
    mat.init(n);
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        mat.d[i][a] = true;
        mat.d[i][b] = true;
        mat.d[i][i] = false;
    }

    mat.pow(k);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if(mat.d[a][b] == true) cout << "death\n";
        else cout << "life\n";
    }

    return 0;
}
