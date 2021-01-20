#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

using lli = long long int;

int n, k;
int a[101];
bool ck[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(ck[i] == true) continue;

        cnt++;

        int current = a[i];
        ck[i] = true;
        for(int j = i + 1; j < n; j++) {
            if(ck[j] == true || a[j] < current) continue;

            current = a[j];
            ck[j] = true;
        }
    }

    if(cnt <= k) cout << "YES";
    else cout << "NO";

    return 0;
}
