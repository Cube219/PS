#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int n, c, d;
lli a, b;
int sf[500001];
lli lcm = 1;
int circle[500001];

vector<int> tmp;

lli gcd(lli a, lli b)
{
    while(b != 0) {
        lli n = a % b;
        a = b;
        b = n;
    }
    return a;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> a >> b >> c >> d;
    for(int i = 1; i <= n; i++) {
        cin >> sf[i];
    }
    
    for(int i = c + 1; i <= n - d; i++) {
        if(circle[i] != 0) continue;

        int cnt = 1, current = i;
        tmp.clear();
        tmp.push_back(i);
        current = sf[current];
        while(current != i) {
            cnt++;
            tmp.push_back(current);
            current = sf[current];
        }
        for(int i = 0; i < tmp.size(); i++) {
            circle[tmp[i]] = cnt;
        }
    }

    for(int i = c + 1; i <= n - d; i++) {
        lli v = (lli)circle[i];
        if(lcm < v) swap(lcm, v);
        if(lcm % v == 0) continue;

        lli g = gcd(lcm, v);
        lcm = (lcm * v) / g;
    }


    b--;
    a--;

    a += lcm - 1;
    a /= lcm;
    b /= lcm;

    cout << b - a + 1;


    return 0;
}
