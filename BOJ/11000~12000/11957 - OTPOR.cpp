#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

using ll = long long int;

int n;
double r[11];
string str;
int mode[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    cin >> str;

    vector<double> st;
    int bnum = 0;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '(') {
            bnum++;
            st.push_back(-bnum);
        } else if(str[i] == ')') {
            double res = 0;
            while(st.back() >= 0.0) {
                if(mode[bnum] == 1) {
                    res += st.back();
                } else {
                    res += 1.0 / st.back();
                }
                st.pop_back();
            }
            if(mode[bnum] == 2) {
                res = 1.0 / res;
            }
            st.pop_back();
            mode[bnum] = 0;
            bnum--;
            st.push_back(res);
        } else {
            if(str[i] == 'R') {
                int num = str[i + 1] - '0';
                st.push_back(r[num]);
                i++;
            } else if(str[i] == '-') {
                mode[bnum] = 1;
            } else {
                mode[bnum] = 2;
            }
        }
    }

    cout << fixed << setprecision(8) << st[0];

    return 0;
}
