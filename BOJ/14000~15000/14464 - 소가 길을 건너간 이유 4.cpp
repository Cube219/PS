#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int c, n;
vector<int> t;
pair<int, int> d[20001];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> c >> n;
    for(int i = 0; i < c; i++) {
        int tt;
        cin >> tt;
        t.push_back(tt);
    }
    for(int i = 0; i < n; i++) {
        cin >> d[i].first >> d[i].second;
    }

    sort(t.begin(), t.end());
    sort(d, d + n, [](const pair<int, int>& l, const pair<int, int>& r) {
        if(l.second == r.second) return l.first < r.first;
        else return l.second < r.second;
    });

    for(int i = 0; i < n; i++) {
        auto it = lower_bound(t.begin(), t.end(), d[i].first);

        if(it != t.end() && *it <= d[i].second) {
            res++;
            t.erase(it);
        }
    }

    cout << res;

    return 0;
}
