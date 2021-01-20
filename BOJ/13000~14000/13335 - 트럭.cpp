#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

using lli = long long int;

int n, w, l;

struct Node
{
    int w;
    int exitTime;
};
queue<int> a;
queue<Node> b;
int bWeight;
int cTime;

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w >> l;
    for(int i = 0; i < n; i++) {
        int aa;
        cin >> aa;
        a.push(aa);
    }

    int currentW = 0;

    while(1) {
        cTime++;

        while(b.empty() == false && b.front().exitTime <= cTime) {
            bWeight -= b.front().w;
            b.pop();
        }

        if(a.empty() == true && b.empty() == true) break;

        if(a.empty() == false) {
            if(bWeight + a.front() <= l) {
                b.push({ a.front(), cTime + w });
                bWeight += a.front();
                a.pop();
            }
        }
    }

    cout << cTime;

    return 0;
}
