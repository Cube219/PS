#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <set>
using namespace std;

using lli = long long int;

int n;
pair<int, int> d[500001];
int res;
set<int> s;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b };
    }

    sort(d, d + n, [](const pair<int, int>& l, const pair<int, int>& r) {
        if(l.second == r.second) return l.first < r.first;
        return l.second < r.second;
    });

    for(int i = 0; i < n; i++) {
        pair<int, int> cur = d[i];

        auto iter = s.lower_bound(cur.first);
        if(iter != s.end()) {
            s.erase(iter);
            res++;
        } else {
            s.insert(cur.second);
        }        
    }
    
    cout << res;

    return 0;
}
