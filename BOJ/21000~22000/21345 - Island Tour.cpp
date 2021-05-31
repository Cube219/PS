#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int mv[401];
int t[401][3];
bool can[3][3][401][401];

struct Range
{
    ll st, ed;
};
Range t1[401], t2[401];

void sett1(int a, int s)
{
    ll cur = 0;
    int idx = s;
    for(int i = 0; i < n; ++i) {
        t1[idx].st = cur;
        t1[idx].ed = cur + t[idx][a];
        cur += t[idx][a] + mv[idx];
        idx++;
        if(idx >= n) idx -= n;
    }
}
void sett2(int a, int s)
{
    ll cur = 0;
    int idx = s;
    for(int i = 0; i < n; ++i) {
        t2[idx].st = cur;
        t2[idx].ed = cur + t[idx][a];
        cur += t[idx][a] + mv[idx];
        idx++;
        if(idx >= n) idx -= n;
    }
}

bool ck()
{
    for(int i = 0; i < n; ++i) {
        if(max(t1[i].st, t2[i].st) < min(t1[i].ed, t2[i].ed)) return false;
    }
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> mv[i];
    }
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> t[j][i];
        }
    }

    for(int i = 0; i <= 1; ++i) {
        for(int j = i + 1; j <= 2; ++j) {
            for(int s1 = 0; s1 < n; ++s1) {
                sett1(i, s1);
                for(int s2 = 0; s2 < n; ++s2) {
                    sett2(j, s2);
                    can[i][j][s1][s2] = ck();
                }
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                if(can[0][1][i][j] == true && can[0][2][i][k] == true && can[1][2][j][k] == true) {
                    cout << i + 1 << " " << j + 1 << " " << k + 1;
                    return 0;
                }
            }
        }
    }
    cout << "impossible";

    return 0;
}
