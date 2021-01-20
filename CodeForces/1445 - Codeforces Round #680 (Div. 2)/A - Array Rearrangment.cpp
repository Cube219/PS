#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, k, a[101];
vector<int> b;
bool res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        b.clear();

        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            int bb;
            cin >> bb;
            b.push_back(bb);
        }
        sort(b.begin(), b.end(), [](int l, int r) {return l > r; });

        res = true;
        for(int i = 0; i < n; i++) {
            auto it = b.begin();
            for(; it != b.end(); it++) {
                if(a[i] + *it <= k) {
                    break;
                }
            }
            if(it == b.end()) {
                res = false;
                break;
            }
            b.erase(it);
        }

        if(res == true) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
