#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;

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
        if(n % 2 == 1) {
            cout << "Bob\n";
        } else {
            bool f = true;
            int cnt = 0;
            while(n > 1) {
                if(n % 2 != 0) {
                    f = false;
                    break;
                }
                n /= 2;
                cnt++;
            }
            if(f == true && cnt % 2 == 1) {
                cout << "Bob\n";
            } else {
                cout << "Alice\n";
            }
        }
    }

    return 0;
}
