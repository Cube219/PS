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
int n, a[101];
bool has[1001];
bool pos;
vector<int> b;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        for(int i = 0; i <= 400; ++i) {
            has[i] = false;
        }
        pos = true;
        b.clear();

        cin >> n;
        bool p = false, neg = false;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            has[a[i] + 200] = true;
            if(a[i] < 0) {
                neg = true;
            } else if(a[i] > 0) {
                p = true;
            }
        }
        if(neg == true) {
            cout << "NO\n";
        } else {
            while(1) {
                bool f = false;
                for(int i = 0; i <= 400; ++i) {
                    for(int j = i + 1; j <= 400; ++j) {
                        if(has[i] == true && has[j] == true) {
                            int v1 = i - 200;
                            int v2 = j - 200;
                            int m = abs(v1 - v2);
                            if(has[m + 200] == false) {
                                has[m + 200] = true;
                                f = true;
                            }
                        }
                    }
                }
                if(f == false) break;
            }
            b.clear();
            for(int i = 0; i <= 400; ++i) {
                if(has[i] == true) {
                    b.push_back(i - 200);
                }
            }
            if(b.size() > 300) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
                cout << b.size() << "\n";
                for(int i = 0; i < b.size(); ++i) {
                    cout << b[i] << " ";
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
