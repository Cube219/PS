#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, k, m;
int st[100001];
int d[100001][40];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> m;
    for(int i = 0; i < n; i++) {
        cin >> st[i];
    }
    for(int i = 1; i <= k; i++) {
        cin >> d[i][0];
    }
    m--;
    int maxI = 0, mm;
    mm = m;
    while(mm > 0) {
        maxI++;
        mm /= 2;
    }

    for(int i = 1; i <= maxI; i++) {
        for(int j = 1; j <= k; j++) {
            int v = j;
            v = d[v][i - 1];
            v = d[v][i - 1];
            d[j][i] = v;
        }
    }

    for(int i = 0; i < 40; i++) {
        if(m % 2 == 1) {
            for(int j = 0; j < n; j++) {
                st[j] = d[st[j]][i];
            }
        }
        m /= 2;
        if(m <= 0) break;
    }

    for(int i = 0; i < n; i++) {
        cout << st[i] << " ";
    }

    return 0;
}
