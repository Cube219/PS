#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int n, a[100001];
vector<int> res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        
        if(cin.eof() == true) {
            break;
        }

        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }

        res.clear();
        res.push_back(-1);
        for(int i = 0; i < n; i++) {
            if(res.back() < a[i]) res.push_back(a[i]);

            auto it = lower_bound(res.begin(), res.end(), a[i]);
            *it = a[i];
        }
        cout << res.size() - 1 << "\n";
    }

    return 0;
}
