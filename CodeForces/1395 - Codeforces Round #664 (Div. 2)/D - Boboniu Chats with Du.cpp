#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

using lli = long long int;

int n, d, m;
lli a[100001];
vector<lli> a1, a2;

lli res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d %d", &n, &d, &m);
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);

    sort(a, a + n);
    res += a[n - 1];
    n--;

    for(int i = 0; i < n; i++) {
        if(a[i] <= m) {
            a1.push_back(a[i]);
            res += a[i];
        } else {
            a2.push_back(a[i]);
        }
    }
    sort(a1.begin(), a1.end(), greater<lli>());

    int remainArea = n - a1.size();
    while(a2.size() > 0) {
        if(remainArea >= d + 1) {
            res += a2.back();
            a2.pop_back();
            remainArea -= d + 1;
        } else {
            bool isPos = true;
            lli deletedA = 0;
            for(int i = remainArea; i < d + 1; i++) {
                if(a1.size() == 0) {
                    isPos = false;
                    break;
                }
                deletedA += a1.back();
                a1.pop_back();
            }
            if(isPos == false) break;

            if(a2.back() > deletedA) {
                res -= deletedA;
                res += a2.back();
                a2.pop_back();
                remainArea = 0;
            } else {
                break;
            }
        }
    }

    printf("%lld", res);

    return 0;
}
