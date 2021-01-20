#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int n, res[100001];
vector<int> a;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int tt;
        cin >> tt;
        a.push_back(tt);
    }
    sort(a.begin(), a.end());

    for(int i = 0; i < n; i+=2) {
        res[i] = a.back();
        a.pop_back();
    }
    int aNum = 0;
    for(int i = 1; i < n; i += 2) {
        res[i] = a[aNum];
        aNum++;
    }

    cout << (n + 1) / 2 - 1 << "\n";
    for(int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }

    return 0;
}
