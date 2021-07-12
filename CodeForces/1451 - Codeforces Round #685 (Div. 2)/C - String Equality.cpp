#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int tNum;
int n, k;
string s1, s2;
int num[30], num2[30];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        cin >> s1 >> s2;

        bool res = true;
        for(int i = 0; i < 26; ++i) {
            num[i] = 0;
            num2[i] = 0;
        }
        for(int i = 0; i < n; ++i) {
            num[s1[i] - 'a']++;
        }
        for(int i = 0; i < n; ++i) {
            num2[s2[i] - 'a']++;
        }

        for(int i = 26 - 1; i >= 0; --i) {
            num2[i] -= num[i];
            if(num2[i] < 0) {
                res = false;
                break;
            }

            if(num2[i] > 0) {
                if(num2[i] % k != 0) {
                    res = false;
                    break;
                }

                for(int j = i - 1; j >= 0; --j) {
                    int cnt1 = num2[i] / k;
                    int cnt2 = num[j] / k;
                    int gap = k * min(cnt1, cnt2);
                    num2[i] -= gap;
                    num[j] -= gap;
                    if(num2[i] == 0) break;
                }
                if(num2[i] > 0) {
                    res = false;
                    break;
                }
            }
        }

        if(res == false) cout << "No\n";
        else cout << "Yes\n";
    }

    return 0;
}
