#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int pos, color;
    bool isright;
};

int n, k, l;
Node d[100001];
ll res[41];
ll dp[41][41];
ll tmp[41][41];

void shift(int v)
{
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < k; ++j) {
            tmp[i][j] = dp[(i + v) % k][j];
        }
    }
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < k; ++j) {
            dp[i][j] = tmp[i][j];
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> l;
    l *= 4;
    for(int i = 0; i < n; ++i) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        d[i] = { a * 4, b, c == 'L' ? false : true };
    }

    for(int i = 0; i < n; ++i) {
        if(d[i].isright == true) {
            res[d[i].color] += l - d[i].pos;
        }
    }
    Node first, last;
    first.pos = -1; last.pos = -1;
    int sum = 0;
    for(int i = 0; i < n; ++i) {
        if(d[i].isright == true) {
            if(first.pos == -1) {
                first = d[i];
                last = d[i];
                sum += d[i].color;
                continue;
            }
            sum += d[i].color;
            shift(d[i].color);
            int dis = (d[i].pos - last.pos) / 2;
            for(int j = 0; j < k; ++j) {
                dp[j][(j + d[i].color) % k] += dis;
            }
            last = d[i];
        } else {
            int curcolor = d[i].color;
            if(last.pos != -1) {
                int bump = (last.pos + d[i].pos) / 2;
                res[curcolor] += d[i].pos - bump;
            }

            for(int j = 0; j < k; ++j) {
                res[j] += dp[curcolor][j];
            }
            curcolor += sum;
            curcolor %= k;

            if(first.pos != -1) {
                int bump = (first.pos + d[i].pos) / 2;
                res[curcolor] += bump;
            } else {
                res[curcolor] += d[i].pos;
            }
        }
    }

    for(int i = 0; i < k; ++i) {
        if(res[i] % 4 == 0) cout << res[i] / 4 << ".0\n";
        else if(res[i] % 4 == 1) cout << res[i] / 4 << ".25\n";
        else if(res[i] % 4 == 2) cout << res[i] / 4 << ".5\n";
        else cout << res[i] / 4 << ".75\n";
    }

    return 0;
}
