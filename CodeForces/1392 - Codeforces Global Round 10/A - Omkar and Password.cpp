#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n, a[200001];
bool isSame;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 0; tt < tNum; tt++) {
        cin >> n;
        cin >> a[0];
        isSame = true;
        for(int i = 1; i < n; i++) {
            cin >> a[i];
            if(a[0] != a[i]) isSame = false;
        }

        if(isSame == true) cout << n << endl;
        else cout << "1" << endl;
    }

    return 0;
}
