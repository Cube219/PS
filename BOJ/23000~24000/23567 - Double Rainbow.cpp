#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, k, cnt1, cnt2, res = INF;
vector<int> d, num1, num2;

void add(int v)
{
    if(num1[v] == 0) cnt1++;
    num1[v]++;
    if(num2[v] == 1) cnt2--;
    num2[v]--;
}

void remove(int v)
{
    if(num1[v] == 1) cnt1--;
    num1[v]--;
    if(num2[v] == 0) cnt2++;
    num2[v]++;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    d.resize(n);
    for(auto& v : d) {
        cin >> v;
        v--;
    }

    num1.resize(k, 0);
    num2.resize(k, 0);
    for(int v : d) {
        if(num2[v] == 0) cnt2++;
        num2[v]++;
    }

    int l = 0, r = -1;
    while(l < n) {
        while(r < n - 1 && cnt1 < k) {
            r++;
            add(d[r]);
        }
        if(cnt1 < k) break;
        while(l <= r && cnt1 >= k) {
            if(cnt2 >= k) res = min(res, r - l + 1);
            remove(d[l]);
            l++;
        }
    }

    if(res == INF) res = 0;
    cout << res;

    return 0;
}
