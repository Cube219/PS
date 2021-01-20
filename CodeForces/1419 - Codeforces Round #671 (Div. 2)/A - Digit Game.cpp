#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n;
char d[1005];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> d;

        if(n % 2 == 1) {
            bool hasOdd = false;
            for(int i = 1; i <= n; i += 2) {
                if((d[i - 1] - '0') % 2 == 1) {
                    hasOdd = true;
                    break;
                }
            }
            if(hasOdd == true) {
                cout << "1\n";
            } else {
                cout << "2\n";
            }
        } else {
            bool hasEven = false;
            for(int i = 2; i <= n; i += 2) {
                if((d[i - 1] - '0') % 2 == 0) {
                    hasEven = true;
                    break;
                }
            }
            if(hasEven == true) {
                cout << "2\n";
            } else {
                cout << "1\n";
            }
        }
    }

    return 0;
}
