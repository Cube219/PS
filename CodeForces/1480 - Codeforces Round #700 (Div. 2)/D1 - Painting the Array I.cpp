#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int a[100001];
vector<int> idx[100001];
int d1, d2;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for(int i = n - 1; i >= 0; --i) {
        if(idx[a[i]].size() == 0) idx[a[i]].push_back(9876554321);
        idx[a[i]].push_back(i);
    }

    d1 = -1;
    d2 = -1;

    for(int i = 0; i < n; ++i) {
        if(d1 == a[i]) {
            if(d2 != a[i]) res++;
            d2 = a[i];
        } else if(d2 == a[i]) {
            if(d1 != a[i]) res++;
            d1 = a[i];
        } else {
            int d1Idx = 987654321;
            int d2Idx = 987654321;
            if(d1 != -1) d1Idx = idx[d1].back();
            if(d2 != -1) d2Idx = idx[d2].back();

            if(d1Idx < d2Idx) {
                if(d1 != a[i]) res++;
                d1 = a[i];
            } else {
                if(d2 != a[i]) res++;
                d2 = a[i];
            }
        }

        idx[a[i]].pop_back();
    }

    cout << res;

    return 0;
}
