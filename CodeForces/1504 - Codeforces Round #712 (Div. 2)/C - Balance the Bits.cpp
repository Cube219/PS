#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
char d[200002];
char r1[200002], r2[200002];
int d1[200002], d2[200002];

bool p(bool f)
{
    if(d[0] == '0' || d[n - 1] == '0') return false;
    int c1 = 0, c2 = 0;
    bool flip = f;
    for(int i = 0; i < n; ++i) {
        if(d[i] == '1') {
            c1++;
            c2++;
            r1[i] = '(';
            r2[i] = '(';
        } else {
            if(flip == false) {
                c1--;
                c2++;
                r1[i] = ')';
                r2[i] = '(';
            } else {
                c1++;
                c2--;
                r1[i] = '(';
                r2[i] = ')';
            }
            flip = !flip;
        }
        d1[i] = c1;
        d2[i] = c2;
    }
    if(c1 != c2 || c1 % 2 == 1) return false;
    int cnt = c1 / 2;
    int m1 = d1[n - 1];
    int m2 = d2[n - 1];
    for(int i = n - 1; i >= 0; --i) {
        m1 = min(m1, d1[i]);
        m2 = min(m2, d2[i]);
        if(d[i] == '1') {
            m1 -= 2;
            m2 -= 2;
            cnt--;
            if(m1 < 0 || m2 < 0) return false;
            r1[i] = ')';
            r2[i] = ')';
        }
        if(cnt == 0) break;
    }
    r1[n] = '\0';
    r2[n] = '\0';
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> d;

        bool pos;
        pos = p(false);
        if(pos == true) {
            cout << "YES\n";
            cout << r1 << "\n";
            cout << r2 << "\n";
        } else {
            pos = p(true);
            if(pos == true) {
                cout << "YES\n";
                cout << r1 << "\n";
                cout << r2 << "\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
