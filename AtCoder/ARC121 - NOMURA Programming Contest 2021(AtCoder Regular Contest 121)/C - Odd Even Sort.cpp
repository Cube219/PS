#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
int d[501];
vector<int> res;

void sw(int idx)
{
    res.push_back(idx);
    swap(d[idx], d[idx + 1]);
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
        for(int i = 1; i <= n; ++i) {
            cin >> d[i];
        }

        res.clear();
        for(int i = n; i >= 2; --i) {
            int idx = 0;
            for(int j = i; j >= 1; --j) {
                if(d[j] == i) {
                    idx = j;
                    break;
                }
            }

            int turn = res.size() + 1;

            if(i == 3) { // 3°³ ³²À½
                turn %= 2;
                while(1) {
                    bool ck = true;
                    for(int j = 1; j <= 3; ++j) {
                        if(d[j] != j) ck = false;
                    }
                    if(ck == true) break;

                    if(turn == 0) { // Â¦¼ö
                        sw(2);
                    } else { // È¦¼ö
                        sw(1);
                    }
                    turn = 1 - turn;
                }
            } else if(i == 2) { // 2°³ ³²À½
                if(idx == i) continue;
                sw(1);
            } else {
                if(idx == i) continue;
                if(idx % 2 != turn % 2) {
                    if(idx == 1) {
                        if(turn % 2 == 0) {
                            sw(2);
                        } else {
                            assert(false);
                        }
                    } else if(idx == 2) {
                        if(turn % 2 == 0) {
                            assert(false);
                        } else {
                            sw(3);
                        }
                    } else if(idx == 3) {
                        sw(2);
                        sw(3);
                        idx = 2;
                    } else {
                        if(turn % 2 == 0) {
                            sw(2);
                        } else {
                            sw(1);
                        }
                    }
                }

                for(int j = idx; j <= i - 1; ++j) {
                    sw(j);
                }
            }
        }

        for(int i = 1; i <= n; ++i) {
            assert(d[i] == i);
        }
        assert(res.size() <= n * n);
        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
            assert(res[i] % 2 == (i + 1) % 2);
        }
        cout << "\n";
    }

    return 0;
}
