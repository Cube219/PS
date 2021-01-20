#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int n, a[101], l[101];
vector<int> t;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        t.clear();

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> l[i];
            if(l[i] == 0) {
                t.push_back(a[i]);
            }
        }

        sort(t.begin(), t.end());

        for(int i = 0; i < n; i++) {
            if(l[i] == 0) {
                a[i] = t.back();
                t.pop_back();
            }
        }

        for(int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
