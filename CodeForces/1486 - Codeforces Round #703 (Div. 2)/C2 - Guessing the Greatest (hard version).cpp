#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    cin >> n;
    int l = 1, r = n;
    cout << "? " << l << " " << r << endl;
    int sIdx;
    cin >> sIdx;

    bool toRight = false;

    if(sIdx == 1) {
        toRight = true;
        l = 1;
    } else if(sIdx == n) {
        r = n;
    } else {
        int tIdx;
        cout << "? 1 " << sIdx << endl;
        cin >> tIdx;

        if(sIdx != tIdx) {
            toRight = true;
            l = sIdx;
        } else {
            r = sIdx;
        }
    }

    if(toRight == true) {
        while(l + 1 < r) {
            int m = (l + r) / 2;

            int qIdx;
            cout << "? " << sIdx << " " << m << endl;
            cin >> qIdx;

            if(sIdx == qIdx) {
                r = m;
            } else {
                l = m;
            }
        }
        cout << "! " << r << endl;
    } else {
        while(l + 1 < r) {
            int m = (l + r) / 2;

            int qIdx;
            cout << "? " << m << " " << sIdx << endl;
            cin >> qIdx;

            if(sIdx == qIdx) {
                l = m;
            } else {
                r = m;
            }
        }
        cout << "! " << l << endl;
    }

    return 0;
}
