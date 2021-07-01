#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int n, s1, s2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;
        s1 = 0, s2 = 0;
        for(int i = 0; i < n; ++i) {
            string str;
            int v;
            cin >> str >> v;
            if(str[0] == 'D') {
                cout << "DROP 2 " << v << "\n";
                s2 += v;
            } else {
                if(s1 >= v) {
                    cout << "TAKE 1 " << v << "\n";
                    s1 -= v;
                    continue;
                }
                if(s1 > 0) {
                    cout << "TAKE 1 " << s1 << "\n";
                    v -= s1;
                    s1 = 0;
                }
                cout << "MOVE 2->1 " << s2 << "\n";
                s1 = s2;
                s2 = 0;
                cout << "TAKE 1 " << v << "\n";
                s1 -= v;
            }
        }
        cout << "\n";
    }

    return 0;
}
