#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, m;
char d[2002][2002];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }

    cout << "1\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num = 4;
            if(i == 0) num--;
            if(i == n - 1) num--;

            if(j == 0) num--;
            if(j == m - 1) num--;

            if((d[i][j] == 'W' && num % 2 == 0) || (d[i][j] == 'B' && num % 2 == 1)) cout << "2";
            else cout << "3";
        }
        cout << "\n";
    }

    return 0;
}
