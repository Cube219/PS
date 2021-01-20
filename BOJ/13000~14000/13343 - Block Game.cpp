#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
ll n, m;

bool canWin(ll a, ll b)
{
    if(a == 0 || b == 0) {
        return false;
    }

    ll newA = a % b;
    if(newA == 0) return true;
    else if(newA + b == a) {
        bool res = canWin(b, newA);
        if(res == true) return false;
        else return true;
    } else {
        return true;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    if(n < m) swap(n, m);

    bool res = canWin(n, m);
    if(res == true) cout << "win";
    else cout << "lose";

    return 0;
}
