#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

using ll = long long int;

struct Node
{
    int idx;
    int height;
    int v;
};

int n;
int d[1000001];
int q;
int dp[1000001];

int process(int k)
{
    deque<Node> dq;
    dq.push_back({ 0, d[0], 0 });
    for(int i = 1; i < n; ++i) {
        while(dq.empty() == false && dq.front().idx < i - k) dq.pop_front();

        int v = 0;
        v = dq.front().v;
        if(dq.front().height <= d[i]) v++;
        dp[i] = v;

        while(dq.empty() == false) {
            if(dq.back().v > dp[i]) dq.pop_back();
            else if(dq.back().v == dp[i]) {
                if(dq.back().height <= d[i]) dq.pop_back();
                else break;
            } else {
                break;
            }
        }
        dq.push_back({ i, d[i], dp[i] });
    }
    return dp[n - 1];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << process(k) << "\n";
    }

    return 0;
}
