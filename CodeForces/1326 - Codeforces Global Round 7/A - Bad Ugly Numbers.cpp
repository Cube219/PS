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

        if(n == 1) {
            cout << "-1\n";
            continue;
        }

        int sum = 2 * (n - 1);
        
        if(sum % 3 == 0) {
            for(int i = 0; i < n - 2; i++) {
                cout << "2";
            }
            cout << "33\n";
        } else {
            for(int i = 0; i < n - 1; i++) {
                cout << "2";
            }
            cout << "3\n";
        }
    }

    return 0;
}
