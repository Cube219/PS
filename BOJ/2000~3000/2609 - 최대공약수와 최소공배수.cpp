#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int gcd(int a, int b)
{
    if(a < b)
    {
        int t = a;
        a = b;
        b = t;
    }
    while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    cin >> a >> b;

    cout << gcd(a, b) << "\n";
    cout << lcm(a, b);

    return 0;
}
