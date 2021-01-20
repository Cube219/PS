#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
int a[10];

int imp[][3] = {
    {1, 3, 2},
{4, 6, 5},
{7, 9, 8},

    {1, 7, 4},
{2, 8, 5},
{3, 9, 6},

{1, 9, 5},
{3, 7, 5}

};
bool f[11];

bool isPos(int x1, int x2)
{
    for(int i = 0; i < 8; i++) {
        int mid = imp[i][2];
        if(f[mid] == true) continue;
        if(imp[i][0] == x1 && imp[i][1] == x2) return false;
        if(imp[i][1] == x1 && imp[i][0] == x2) return false;
    }

    return true;
}

bool res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    f[a[0]] = true;

    res = true;
    for(int i = 1; i < n; i++) {
        if(f[a[i]] == true) {
            res = false;
            break;
        }

        if(isPos(a[i - 1], a[i]) == false) {
            res = false;
            break;
        }

        f[a[i]] = true;
    }

    if(res == true) cout << "YES";
    else cout << "NO";

    return 0;
}
