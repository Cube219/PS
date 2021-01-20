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

    
    int st = 0, ed = a.size() - 1;
    int resI = 0;
    while(st <= ed) {
        res[resI++] = a[ed];

        if(st != ed) {
            res[resI++] = a[st];
        }
        st++;
        ed--;
    }

    int cnt = 0;

    int replaceIdx = 1;

    for(int i = 1; i < n - 1; i += 2) {
        if(res[i - 1] > res[i] && res[i] < res[i + 1]) {
            cnt++;
            continue;
        }

        int left = res[replaceIdx];
        int right = res[i];

        if(res[replaceIdx - 1] > right && right < res[replaceIdx + 1]) {
            if(res[i - 1] > left && left < res[i + 1]) {
                swap(res[replaceIdx], res[i]);
                cnt++;
                replaceIdx += 2;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    cout << cnt << "\n";
    for(int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }

    return 0;
}
