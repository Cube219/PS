#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, a[30001], minVs[30001], minVs2[30001];
bool res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        int minV = 987654321;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(minV > a[i]) minV = a[i];
            minVs[i] = minV;
        }
        minV = 987654321;
        for(int i = n - 1; i >= 0; i--) {
            if(minV > a[i]) minV = a[i];
            minVs2[i] = minV;
        }

        res = true;
        int current = a[n - 1];
        int offset = 0;
        for(int i = n - 2; i >= 0; i--) {
            if(a[i] - offset <= current) {
                current = a[i] - offset;
                continue;
            }

            offset += (a[i] - offset) - current;
            if(minVs[i] - offset < 0) {
                res = false;
                break;
            }
            current = a[i] - offset;
        }
        if(res == true) {
            cout << "YES\n";
            continue;
        }

        res = true;
        current = a[0];
        offset = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] - offset <= current) {
                current = a[i] - offset;
                continue;
            }

            offset += (a[i] - offset) - current;
            if(minVs2[i] - offset < 0) {
                res = false;
                break;
            }
            current = a[i] - offset;
        }

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
