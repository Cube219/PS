#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n;
lli k;
int a[200001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 0; tt < tNum; tt++) {
        int maxV = -1000000001;

        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(maxV < a[i]) maxV = a[i];
        }

        int realMax = maxV;

        k--;
        realMax = -1000000001;
        for(int i = 0; i < n; i++) {
            a[i] = maxV - a[i];
            if(realMax < a[i]) realMax = a[i];
        }

        if(k % 2 == 1) {
            for(int i = 0; i < n; i++) {
                a[i] = realMax - a[i];
            }
        }

        for(int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
