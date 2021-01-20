#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, k, s;
int d[401][401];

constexpr int INF = 987654321;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i != j) {
                d[i][j] = INF;
            }
        }
    }

    for(int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        d[a][b] = 1;
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    cin >> s;
    for(int i = 0; i < s; i++) {
        int a, b;
        cin >> a >> b;
        if(d[a][b] != INF) cout << "-1\n";
        else if(d[b][a] != INF) cout << "1\n";
        else cout << "0\n";
    }

    return 0;
}
