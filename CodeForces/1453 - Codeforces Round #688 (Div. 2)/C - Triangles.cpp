#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
char d[2002][2002];
ll res[10];
ll rMin[2002], cMin[2002], rMax[2002], cMax[2002];

void init(int x)
{
    for(int i = 0; i < n; i++) {
        rMin[i] = 987654321;
        cMin[i] = 987654321;
        rMax[i] = -1;
        cMax[i] = -1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(d[i][j] != x + '0') continue;

            if(rMax[i] < j) rMax[i] = j;
            if(rMin[i] > j) rMin[i] = j;
            if(cMax[j] < i) cMax[j] = i;
            if(cMin[j] > i) cMin[j] = i;
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }

        for(int num = 0; num <= 9; num++) {
            init(num);
            res[num] = 0;

            for(int i = 0; i < n; i++) {
                if(rMax[i] != -1 && rMax[i] != rMin[i]) {
                    ll w = rMax[i] - rMin[i];
                    ll h = max(i, n - i - 1);
                    if(res[num] < w * h) res[num] = w * h;
                }
                if(cMax[i] != -1 && cMax[i] != cMin[i]) {
                    ll w = cMax[i] - cMin[i];
                    ll h = max(i, n - i - 1);
                    if(res[num] < w * h) res[num] = w * h;
                }
            }

            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    if(rMax[i] != -1 && rMax[j] != -1) {
                        ll w = max(rMax[i], n - rMin[i] - 1);
                        w = max(w, rMax[j]);
                        w = max(w, n - rMin[j] - 1);
                        ll h = j - i;
                        if(res[num] < w * h) res[num] = w * h;
                    }
                    if(cMax[i] != -1 && cMax[j] != -1) {
                        ll w = max(cMax[i], n - cMin[i] - 1);
                        w = max(w, cMax[j]);
                        w = max(w, n - cMin[j] - 1);
                        ll h = j - i;
                        if(res[num] < w * h) res[num] = w * h;
                    }
                }
            }
        }

        for(int i = 0; i <= 9; i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
