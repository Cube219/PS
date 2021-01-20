#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, a[2002];
bool isUsed[2002];
vector<pair<int, int>> res;
bool pos;

bool p()
{
    int cur = a[n - 1];

    for(int i = n - 2; i >= 0; i--) {
        if(isUsed[i] == true) continue;
        int right = a[i];
        for(int j = 0; j < i; j++) {
            if(isUsed[j] == true) continue;
            int left = a[j];
            if(left + right == cur) {
                isUsed[i] = true;
                isUsed[j] = true;
                res.push_back({ a[i], a[j] });
                cur = right;
                break;
            } else if(left + right > cur) {
                return false;
            }
        }
        if(isUsed[i] == false) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res.clear();
        pos = true;

        cin >> n;
        n *= 2;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);

        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < n; j++) isUsed[j] = false;

            isUsed[n - 1] = true;
            isUsed[i] = true;
            res.push_back({ a[i], a[n - 1] });
            if(p() == true) break;
            res.clear();
        }

        if(res.size() == 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            cout << res[0].first + res[0].second << "\n";
            for(int i = 0; i < res.size(); i++) {
                cout << res[i].first << " " << res[i].second << "\n";
            }
        }
    }

    return 0;
}
