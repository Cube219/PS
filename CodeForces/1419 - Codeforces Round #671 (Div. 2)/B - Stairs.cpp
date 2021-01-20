#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
lli x;
lli current;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        current = 1;
        res = 0;

        cin >> x;

        while(1) {
            lli req = current * (current + 1) / 2;
            if(x - req < 0) break;

            res++;
            x -= req;
            current *= 2;
            current++;
        }
        cout << res << "\n";
    }

    return 0;
}
