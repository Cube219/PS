#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
int r[102], b[102];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        int c = 0;
        int rMax = 0;

        for(int i = 0; i < n; i++) {
            cin >> r[i];
            c += r[i];
            if(rMax < c) rMax = c;
        }
        cin >> m;
        c = 0;
        int bMax = 0;
        for(int i = 0; i < m; i++) {
            cin >> b[i];
            c += b[i];
            if(bMax < c) bMax = c;
        }

        cout << rMax + bMax << "\n";
    }

    return 0;
}
