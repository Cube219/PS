#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, l, k;

struct Node
{
    int a;
    int b;
    bool isUsed;
};

Node d[102];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l >> k;
    for(int i = 0; i < n; i++) {
        cin >> d[i].a >> d[i].b;
        d[i].isUsed = false;
    }

    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.b < r.b;
    });

    for(int i = 0; i < n; i++) {
        if(d[i].b > l) break;
        if(k == 0) break;
        res += 140;
        k--;
        d[i].isUsed = true;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.a < r.a;
    });
    for(int i = 0; i < n; i++) {
        if(d[i].a > l) break;
        if(k == 0) break;
        if(d[i].isUsed == true) continue;
        res += 100;
        k--;
    }

    cout << res;

    return 0;
}
