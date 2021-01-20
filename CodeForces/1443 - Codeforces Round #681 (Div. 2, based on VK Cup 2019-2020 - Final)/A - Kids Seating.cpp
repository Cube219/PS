#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        int nn = n * 4 - 2;
        for(int i = 0; i < n; i++) {
            cout << nn << " ";
            nn -= 2;
        }
        cout << "\n";
    }

    return 0;
}
