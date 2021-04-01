#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, p[100001];
int fibo[100001], fNum;
int maxp;
int d[3000001];
bool has[31];

void init()
{
    fibo[0] = 1;
    fibo[1] = 1;
    int i = 2;
    while(1) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        if(fibo[i] > 3000000) break;
        i++;
    }
    fNum = i - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    for(int i = 1; i <= 3000000; ++i) {
        for(int j = 0; j < 30; ++j) {
            has[j] = false;
        }
        for(int j = 1; j <= fNum; ++j) {
            int v = i - fibo[j];
            if(v < 0) break;
            has[d[v]] = true;
        }
        bool ck = false;
        for(int j = 0; j < 30; ++j) {
            if(has[j] == false) {
                d[i] = j;
                ck = true;
                break;
            }
        }
        if(ck == false) cout << "ERROR";
    }

    int res = 0;
    for(int i = 0; i < n; ++i) {
        res = res ^ d[p[i]];
    }
    if(res == 0) cout << "cubelover";
    else cout << "koosaga";

    return 0;
}
