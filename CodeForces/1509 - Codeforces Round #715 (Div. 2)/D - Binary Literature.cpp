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

int tNum;
int n;
string s[3];
bool finish;

bool ck(int st, string& s1, string& s2)
{
    int idx = 0;
    for(int i = 0; i < n * 2; ++i) {
        if(s1[i] == s2[st + idx]) {
            idx++;
            if(idx == n) break;
        }
    }
    if(idx >= n) {
        for(int i = 0; i < st; ++i) {
            cout << s2[i];
        }
        for(int i = 0; i < n * 2; ++i) {
            cout << s1[i];
        }
        for(int i = st + idx; i < n * 2; ++i) {
            cout << s2[i];
        }
        cout << "\n";
        return true;
    }
    return false;
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
        cin >> n;
        cin >> s[0] >> s[1] >> s[2];
        finish = false;

        for(int i = 0; i <= n; ++i) {
            for(int t1 = 0; t1 < 3; ++t1) {
                for(int t2 = 0; t2 < 3; ++t2) {
                    if(t1 == t2) continue;
                    if(ck(i, s[t1], s[t2]) == true) {
                        finish = true;
                        break;
                    }
                    if(ck(n - i, s[t1], s[t2]) == true) {
                        finish = true;
                        break;
                    }
                }
                if(finish == true) break;
            }
            if(finish == true) break;
        }
    }

    return 0;
}
