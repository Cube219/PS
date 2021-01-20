#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, x;
int sum;
int cnt;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        sum = 0;
        cnt = 0;

        cin >> n >> x;
        bool has = false;
        bool same = false;
        for(int i = 0; i < n; i++) {
            int aa;
            cin >> aa;

            if(aa != x) {
                has = true;
                sum += aa;
                cnt++;
            } else {
                same = true;
            }
        }

        if(has == false) {
            cout << "0\n";
            continue;
        }

        if(n == 1) {
            cout << "1\n";
        } else {
            if(same == true || n * x == sum) {
                cout << "1\n";
            } else {
                cout << "2\n";
            }
        }
    }

    return 0;
}
