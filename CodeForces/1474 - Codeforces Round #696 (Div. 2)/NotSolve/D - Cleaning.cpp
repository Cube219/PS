#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
ll a[200002];
ll b[200002];
bool isPos;

void cp()
{
    for(int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

int ck(int i1, int i2)
{
    if(i1 != i2) swap(b[i1], b[i2]);

    for(int i = 0; i < n - 1; i++) {
        if(b[i] == 0) continue;
        if(b[i + 1] - b[i] < 0) {
            return i;
        } else {
            b[i + 1] -= b[i];
            b[i] = 0;
        }
    }
    if(b[n - 1] != 0) {
        return n-1;
    }
    return -1;
}

int ckRev(int i1, int i2)
{
    if(i1 != i2) swap(b[i1], b[i2]);

    for(int i = n - 1; i >= 1; i--) {
        if(b[i] == 0) continue;
        if(b[i - 1] - b[i] < 0) {
            return i;
        } else {
            b[i - 1] -= b[i];
            b[i] = 0;
        }
    }
    if(b[0] != 0) {
        return 0;
    }
    return -1;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }

        isPos = false;

        // l->r
        cp();
        int res = ck(0, 0);
        int idx = res;
        if(res == -1) {
            isPos = true;
        } else {
            if(idx + 1 < n) {
                cp();
                res = ck(idx, idx+1);

                if(res == -1) isPos = true;
            }
            if(idx - 1 >= 0) {
                cp();
                res = ck(idx, idx-1);

                if(res == -1) isPos = true;
            }
            if(idx + 2 < n) {
                cp();
                res = ck(idx + 1, idx + 2);
                if(res == -1) isPos = true;
            }
            if(idx - 2 >= 0) {
                cp();
                res = ck(idx - 1, idx - 2);
                if(res == -1) isPos = true;
            }
        }

        // r->l
        if(isPos == false) {
            cp();
            res = ckRev(0, 0);
            idx = res;
            if(res == -1) {
                isPos = true;
            } else {
                if(idx + 1 < n) {
                    cp();
                    res = ckRev(idx, idx + 1);

                    if(res == -1) isPos = true;
                }
                if(idx - 1 >= 0) {
                    cp();
                    res = ckRev(idx, idx - 1);

                    if(res == -1) isPos = true;
                }
                if(idx + 2 < n) {
                    cp();
                    res = ckRev(idx + 1, idx + 2);
                    if(res == -1) isPos = true;
                }
                if(idx - 2 >= 0) {
                    cp();
                    res = ckRev(idx - 1, idx - 2);
                    if(res == -1) isPos = true;
                }
            }
        }

        if(isPos == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
