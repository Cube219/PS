#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

using lli = long long int;

int n;
lli l;
struct Node
{
    lli s;
    lli e;
};
Node edD[100001];
bool operator>(const Node& l, const Node& r)
{
    return l.s > r.s;
}
priority_queue<Node, vector<Node>, greater<Node>> pq;
lli minS = 987654321;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        edD[i] = { a, b };

        if(minS > a) minS = a;
    }
    cin >> l;

    sort(edD, edD + n, [](const Node& l, const Node& r) { return l.e < r.e; });

    lli currentS, currentE;
    currentS = minS;
    currentE = currentS + l;

    int idx;
    int cnt = 0;
    for(idx = 0; idx < n; idx++) {
        if(edD[idx].e > currentE) break;

        pq.push(edD[idx]);
        cnt++;
    }
    res = cnt;

    for(; idx < n; idx++) {
        currentE = edD[idx].e;
        currentS = currentE - l;

        if(edD[idx].s >= currentS) {
            pq.push(edD[idx]);
            cnt++;
        }

        while(pq.empty() == false) {
            Node f = pq.top();
            if(f.s < currentS) {
                pq.pop();
                cnt--;
            } else {
                break;
            }
        }

        if(cnt > res) res = cnt;
    }

    cout << res;

    return 0;
}
