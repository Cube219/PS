#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int zero, one, k;
bool pos = false;
char s1[200005], s2[200005];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> zero >> one >> k;
    int cnt = 0;
    for(int i = 0; i < one; ++i) {
        s1[cnt] = '1';
        s2[cnt] = '1';
        cnt++;
    }
    for(int i = 0; i < zero; ++i) {
        s1[cnt] = '0';
        s2[cnt] = '0';
        cnt++;
    }
    s1[zero + one] = '\0';
    s2[zero + one] = '\0';

    if(one == 1) {
        if(k == 0) {
            pos = true;
        } else {
            pos = false;
        }
    } else if(zero >= k) {
        s2[one - 1] = '0';
        s2[one + k - 1] = '1';
        pos = true;
    } else {
        s2[one - 1] = '0';
        s2[one + zero - 1] = '1';
        int cnt = zero;

        for(int i = one - 2; i >= 1; i--) {
            cnt++;
            s2[i] = '0';
            s2[i + 1] = '1';
            if(cnt == k) {
                pos = true;
                break;
            }
        }
    }

    if(pos == true) {
        cout << "Yes\n";
        cout << s1 << "\n";
        cout << s2 << "\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
