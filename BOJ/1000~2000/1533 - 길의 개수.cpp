#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, s, e;
char str[101];
ll t;
ll d[55][55];
ll c[55];
int newN;

constexpr ll MOD = 1000003;

ll res[55][55], tmp[55][55];

void mul()
{
    for(int i = 0; i < n * 5; ++i) {
        for(int j = 0; j < n * 5; ++j) {
            tmp[i][j] = 0;
            for(int k = 0; k < n * 5; ++k) {
                tmp[i][j] = (tmp[i][j] + res[i][k] * d[k][j]) % MOD;
            }
        }
    }

    for(int i = 0; i < n * 5; ++i) {
        for(int j = 0; j < n * 5; ++j) {
            res[i][j] = tmp[i][j];
        }
    }
}

void pow()
{
    for(int i = 0; i < n * 5; ++i) {
        for(int j = 0; j < n * 5; ++j) {
            tmp[i][j] = 0;
            for(int k = 0; k < n * 5; ++k) {
                tmp[i][j] = (tmp[i][j] + res[i][k] * res[k][j]) % MOD;
            }
        }
    }

    for(int i = 0; i < n * 5; ++i) {
        for(int j = 0; j < n * 5; ++j) {
            res[i][j] = tmp[i][j];
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s >> e >> t;
    s--; e--;

    for(int i = 0; i < n; ++i) {
        cin >> str;
        for(int j = 0; j < n; ++j) {
            int g = str[j] - '0';
            if(g >= 1) {
                d[j * 5 + g - 1][i * 5] = 1;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            d[i * 5 + j][i * 5 + j + 1] = 1;
        }
    }

    for(int i = 0; i < n * 5; ++i) {
        for(int j = 0; j < n * 5; ++j) {
            res[i][j] = d[i][j];
        }
    }

    c[s * 5] = 1;

    vector<int> bits;
    while(t > 1) {
        bits.push_back(t % 2);
        t /= 2;
    }

    while(bits.empty() == false) {
        pow();
        if(bits.back() == 1) {
            mul();
        }
        bits.pop_back();
        t /= 2;
    }

    ll rr = 0;
    for(int i = 0; i < n * 5; ++i) {
        rr = (rr + c[i] * res[e * 5][i]) % MOD;
    }

    cout << res[e * 5][s * 5];

    return 0;
}
