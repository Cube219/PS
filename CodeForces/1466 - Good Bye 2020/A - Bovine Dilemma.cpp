#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, d[101];
int res = 0;

bool has[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        for(int i = 1; i <= 100; i++) has[i] = false;

        res = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }

        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 1; j < n; j++) {
                int l = d[j] - d[i];
                if(has[l] == false) {
                    has[l] = true;
                    res++;
                }
            }
        }

        cout << res << endl;
    }

    return 0;
}
