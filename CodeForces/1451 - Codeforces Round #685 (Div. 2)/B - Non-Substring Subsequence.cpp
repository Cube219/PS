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
int n, q;
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> q;
        cin >> str;

        for(int i = 0; i < q; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            bool pos = false;

            for(int i = b + 1; i < n; ++i) {
                if(str[b] == str[i]) {
                    pos = true;
                    break;
                }
            }
            for(int i = a - 1; i >= 0; --i) {
                if(str[a] == str[i]) {
                    pos = true;
                    break;
                }
            }

            if(pos == false) cout << "NO\n";
            else cout << "YES\n";
        }
    }

    return 0;
}
