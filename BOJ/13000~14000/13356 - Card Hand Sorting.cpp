#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
int d[101];
char buf[10];

int map[200];
int res;
int d2[101];

int toint(char a, char b)
{
    int res = 0;
    if('0' <= a && a <= '9') res = a - '0';
    else if(a == 'T') res = 10;
    else if(a == 'J') res = 11;
    else if(a == 'Q') res = 12;
    else if(a == 'K') res = 13;
    else res = 14;

    if(b == 's') res += 20;
    else if(b == 'h') res += 40;
    else if(b == 'd') res += 60;
    else res += 80;
    return res;
}

constexpr int NINF = -2147483648;

int lis_num(int* d, int dNum)
{
    vector<int> res;
    res.push_back(NINF);

    for(int i = 0; i < dNum; i++) {
        if(res.back() < d[i]) res.push_back(d[i]);
        else {
            auto it = lower_bound(res.begin(), res.end(), d[i]);
            *it = d[i];
        }
    }

    return res.size() - 1;
}

bool has[4];
void bt(int idx, int cnum)
{
    if(idx == 4) {
        for(int i = 0; i < n; ++i) {
            d2[i] = map[d[i]];
        }
        res = max(res, lis_num(d2, n));
        return;
    }

    for(int i = 0; i < 4; i++) {
        if(has[i] == true) continue;

        has[i] = true;

        int tmp = 20 * (i + 1);
        // inc order
        for(int j = 0; j <= 14; ++j) {
            map[tmp + j] = cnum + j;
        }
        bt(idx + 1, cnum + 15);

        // dec order
        for(int j = 0; j <= 14; ++j) {
            map[tmp + 14 - j] = cnum + j;
        }
        bt(idx + 1, cnum + 15);

        has[i] = false;
    }
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
        cin >> buf;
        d[i] = toint(buf[0], buf[1]);
    }

    bt(0, 0);

    cout << n - res;

    return 0;
}
