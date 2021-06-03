#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int x;
bool can[2001];

void init()
{
    //11
    can[11] = true;
    for(int i = 12; i <= 2000; i++) {
        if(can[i - 11] == true) can[i] = true;
    }
    //111
    can[111] = true;
    for(int i = 112; i <= 2000; i++) {
        if(can[i - 111] == true) can[i] = true;
    }
    //1111
    can[1111] = true;
    for(int i = 1112; i <= 2000; i++) {
        if(can[i - 1111] == true) can[i] = true;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x;
        if(x <= 2000) {
            if(can[x] == false) cout << "NO\n";
            else cout << "YES\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
