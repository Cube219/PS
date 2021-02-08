#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> d;
int d1, d2;
vector<int> nx[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int before = -1;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if(before != a) d.push_back(a);
        before = a;
    }

    for(int i = 0; i <= n; ++i) {
        nx[i].push_back(987654321);
    }

    n = d.size();
    for(int i = n - 1; i >= 0; --i) {
        nx[d[i]].push_back(i);
    }

    d1 = 0;
    d2 = 0;

    int res = 0;

    for(int i = 0; i < n; ++i) {
        if(d1 == d[i] || d2 == d[i]) {
            nx[d[i]].pop_back();
            continue;
        }

        res++;
        if(nx[d1].back() < nx[d2].back()) d2 = d[i];
        else d1 = d[i];

        nx[d[i]].pop_back();
    }

    cout << res;

    return 0;
}
