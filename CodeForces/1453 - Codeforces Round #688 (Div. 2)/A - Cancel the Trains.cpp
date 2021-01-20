#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
int l[101], bot[101];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;

        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            cin >> bot[i];
        }
        for(int i = 1; i <= m; i++) {
            cin >> l[i];
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(bot[i] == l[j]) {
                    res++;
                }
            }
        }
        
        cout << res << "\n";
    }

    return 0;
}
