#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int h;
int nn;
int usenum, bnum;

int query(int st, int idx, int num)
{
    usenum++;
    bnum += num;
    cout << "? " << st << " " << idx << " " << num << endl;
    int res;
    cin >> res;
    return res;
}

int main(void)
{
    cin >> n;
    if(n == 1) {
        cout << "! 1";
        return 0;
    }
    // n--;
    nn = n;
    int res;
    res = query(1, 1, n);
    h = res;

    int st = 0, cur = 0;
    int i = 2;
    while(n > 1) {
        if(n == 2) {
            res = query(cur + 1, nn, 1);
            if(res != h) cur |= (i >> 1);
            break;
        }
        // cout << "n : " << n << "\n";
        int cnt = (n - 1) / 2 + 1;
        if(cnt < n - cnt) {
            res = query(cur + 1, i, cnt);
            if(res != h) {
                cur |= (i >> 1);
                n -= cnt;
            } else {
                n = cnt;
            }
        } else {
            int tcur = (cur | (i >> 1));
            res = query(tcur + 1, i, n - cnt);
            if(res == h) {
                cur |= (i >> 1);
                n -= cnt;
            } else {
                n = cnt;
            }
        }
        i *= 2;
    }

    cout << "! " << cur + 1;

    //cout << "\n";
    //cout << usenum << " / " << bnum;

    return 0;
}
