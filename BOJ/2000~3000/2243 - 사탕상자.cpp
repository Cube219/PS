#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
using namespace std;

using lli = long long int;
int n;
int t[3000001];
int stLeaf;
int res;

void search(int cl, int cr, int node, int num)
{
    if(cl == cr) {
        res = cl + 1;
        return;
    }

    int m = (cl + cr) / 2;
    int left = t[node * 2];
    int right = t[node * 2 + 1];
    
    if(left >= num) {
        search(cl, m, node * 2, num);
    } else {
        search(m + 1, cr, node * 2 + 1, num - left);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    stLeaf = 1;
    while(stLeaf < 1000000) {
        stLeaf *= 2;
    }

    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b;
        if(a == 1) {
            res = -1;

            search(0, stLeaf - 1, 1, b);

            cout << res << "\n";

            int node = stLeaf + res - 1;
            while(node > 0) {
                t[node]--;
                node /= 2;
            }
        } else {
            cin >> c;

            int node = stLeaf + b - 1;
            while(node > 0) {
                t[node] += c;
                node /= 2;
            }
        }
    }

    return 0;
}
