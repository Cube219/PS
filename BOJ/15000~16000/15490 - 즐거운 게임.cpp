#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int n, a[3001];
int dp[3001][3001][2];

bool pEven[2];

void Change(int turn, lli v)
{
    if(v % 2 == 1) {
        pEven[turn] = !pEven[turn];
    }
}

// dp: l~r이고, 현제 even일 때 이길 수 있는가
int p(int l, int r, int turn)
{
    bool isEven = pEven[turn];
    if(dp[l][r][isEven] != 0) return dp[l][r][isEven];
    if(l > r) {
        if(isEven == true) {
            dp[l][r][isEven] = 1;
            return 1;
        } else {
            dp[l][r][isEven] = -1;
            return -1;
        }
    }

    int res = -1, t;
    // left 1
    Change(turn, a[l]);
    t = p(l + 1, r, 1 - turn);
    if(t == -1) res = 1;
    Change(turn, a[l]);

    // right 1
    Change(turn, a[r]);
    t = p(l, r - 1, 1 - turn);
    if(t == -1) res = 1;
    Change(turn, a[r]);

    if(r - l > 0) {
        // left 2
        Change(turn, (lli)(a[l]) + (lli)(a[l + 1]));
        t = p(l + 2, r, 1 - turn);
        if(t == -1) res = 1;
        Change(turn, (lli)(a[l]) + (lli)(a[l + 1]));
        // right 2
        Change(turn, (lli)(a[r]) + (lli)(a[r - 1]));
        t = p(l, r - 2, 1 - turn);
        if(t == -1) res = 1;
        Change(turn, (lli)(a[r]) + (lli)(a[r - 1]));
    }

    dp[l][r][isEven] = res;

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pEven[0] = pEven[1] = true;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int res = p(0, n - 1, 0);

    if(res == 1) cout << "Yes";
    else cout << "No";

    return 0;
}
