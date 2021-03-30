#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

int n, m;
bool isStart;
int cur[100011];
bool has[100011];
int res[100011];
bool visit[100011];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cur[0] = 1;

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m; ++j) {
            visit[j] = false;
            if(cur[j] > 0) has[j] = true;
            else has[j] = false;
        }

        ll a, b, c;
        cin >> a >> b >> c;

        for(int j = m; j >= 0; j--) {
            if(has[j] == false || visit[j] == true) continue;
            ll curV = j;
            for(int k = 0; k < c; ++k) {
                if(a == 1) {
                    curV += b / 100000;
                    if(b % 100000 != 0) curV++;
                } else {
                    ll tmp = curV * b;
                    if(tmp % 100000 != 0) {
                        tmp /= 100000;
                        tmp++;
                    } else {
                        tmp /= 100000;
                    }
                    curV = tmp;
                }
                ll idx = curV;
                if(idx > m) break;
                if(visit[idx] == true) break;

                visit[idx] = true;
                cur[idx] = i + 1;
                if(res[idx] == 0) res[idx] = i + 1;
            }
        }
    }

    for(int i = 1; i <= m; ++i) {
        if(res[i] == 0) res[i] = -1;
        cout << res[i] << " ";
    }

    return 0;
}
