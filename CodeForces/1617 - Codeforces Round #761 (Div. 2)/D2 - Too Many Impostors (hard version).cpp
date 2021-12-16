#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> d;

int query(int a, int b, int c)
{
    cout << "? " << a << " " << b << " " << c << endl;

    int res;
    cin >> res;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    // freopen("input.txt", "r", stdin);
#endif

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;

        vector<char> is0(n + 1, 0);
        int idx = -1, idx2 = -1;
        for(int i = 1; i <= n; i += 3) {
            int r = query(i, i + 1, i + 2);
            if(r == 1) {
                idx = i;
            } else {
                idx2 = i;
            }
            if(r == 0) is0[i] = true;
            else is0[i] = false;
        }

        int widx = -1, bidx = -1;

        // idx, idx + 1
        int r = query(idx, idx + 1, idx2);
        int r2 = query(idx, idx + 1, idx2 + 1);
        if(r == 1 && r2 == 1) {
            widx = idx;

            // 임포 구하기
            // idx2, idx2 + 1
            r = query(idx2, idx2 + 1, widx);
            if(r == 0) {
                bidx = idx2;
            } else {
                bidx = idx2 + 2;
            }
        } else {
            if(r == 0) bidx = idx2;
            else if(r2 == 0) bidx = idx2 + 1;
        }

        // idx, idx + 2
        if(widx == -1) {
            r = query(idx, idx + 2, bidx);
            if(r == 1) {
                widx = idx;
            } else {
                // idx + 1, idx + 2
                widx = idx + 1;
            }
        }

        int res = 0;
        vector<char> isimp(n + 1, false);
        for(int i = 1; i <= n; i += 3) {
            if(i <= widx && widx < i + 3) {
                for(int j = 0; j < 3; ++j) {
                    if(i + j == widx) continue;
                    r = query(widx, bidx, i + j);
                    if(r == 0) isimp[i + j] = true;
                }
            } else if(i <= bidx && bidx < i + 3) {
                for(int j = 0; j < 3; ++j) {
                    if(i + j == bidx) {
                        isimp[i + j] = true;
                        continue;
                    }
                    r = query(widx, bidx, i + j);
                    if(r == 0) isimp[i + j] = true;
                }
            } else {
                if(is0[i] == true) {
                    r = query(widx, i, i + 1);
                    if(r == 0) {
                        isimp[i] = true;
                        isimp[i + 1] = true;
                        r = query(widx, i + 1, i + 2);
                        if(r == 0) {
                            isimp[i + 2] = true;
                        }
                    } else {
                        isimp[i + 2] = true;
                        r = query(widx, i + 1, i + 2);
                        if(r == 0) {
                            isimp[i + 1] = true;
                        } else {
                            isimp[i] = true;
                        }
                    }
                } else {
                    r = query(bidx, i, i + 1);
                    if(r == 0) {
                        r = query(bidx, i + 1, i + 2);
                        if(r == 0) {
                            isimp[i + 1] = true;
                        } else {
                            isimp[i] = true;
                        }
                    } else {
                        r = query(bidx, i + 1, i + 2);
                        if(r == 0) {
                            isimp[i + 2] = true;
                        } else {
                            
                        }
                    }
                }
            }
        }

        for(int i = 1; i <= n; ++i) {
            if(isimp[i] == true) res++;
        }
        cout << "! " << res << " ";
        for(int i = 1; i <= n; ++i) {
            if(isimp[i] == false) continue;
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
