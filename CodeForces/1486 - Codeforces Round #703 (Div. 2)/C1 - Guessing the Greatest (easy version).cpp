#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int n;
int res;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
 
    cin >> n;
    int l = 1, r = n;
    cout << "? " << l << " " << r << endl;
    int sIdx;
    cin >> sIdx;
    while(1) {
        int m = (l + r) / 2;
        int lIdx, rIdx;
 
        if(l + 2 == r) {
            int tIdx;
            cout << "? " << l << " " << l + 1 << endl;
            cin >> tIdx;
 
            if(sIdx == m + 1) {
                if(tIdx == l) res = l + 1;
                else res = l;
                break;
            } else {
                if(sIdx == tIdx) {
                    if(l == sIdx) res = l + 1;
                    else res = l;
                    break;
                } else {
                    res = r;
                    break;
                }
            }
        } else if(l + 1 == r) {
            if(l == sIdx) res = r;
            else res = l;
            break;
        }
 
        cout << "? " << l << " " << m << endl;
        cin >> lIdx;
 
        cout << "? " << m + 1 << " " << r << endl;
        cin >> rIdx;
 
        if(lIdx == sIdx) {
            r = m;
        } else if(rIdx == sIdx) {
            l = m + 1;
        } else {
            if(m + 1 <= sIdx) {
                r = m;
                sIdx = lIdx;
            } else {
                l = m + 1;
                sIdx = rIdx;
            }
        }
    }
 
    cout << "! " << res;
 
    return 0;
}
