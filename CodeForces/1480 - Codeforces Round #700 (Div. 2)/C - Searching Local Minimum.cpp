#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
int d[100001];

int query(int x)
{
    if(d[x] == 0) {
        cout << "? " << x << endl;
        cin >> d[x];
    }

    return d[x];
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    cin >> n;
    int s = 1;
    int e = n;
    int sv = 987654321;
    int ev = 987654321;

    while(s < e) {
        int m = (s + e) / 2;

        int m1, m2;

        m1 = query(m);
        m2 = query(m + 1);

        if(m1 < m2) {
            e = m;
            ev = m;
        } else {
            s = m + 1;
            ev = m2;
        }
    }
    if(sv < ev) cout << "! " << s;
    else cout << "! " << e;

    return 0;
}
