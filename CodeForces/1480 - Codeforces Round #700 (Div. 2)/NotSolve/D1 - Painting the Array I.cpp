#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int n;
int a[100001];
vector<int> d1, d2;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    d1.push_back(-1);
    d2.push_back(-1);
 
    for(int i = 0; i < n; ++i) {
        if(d1.back() != a[i]) {
            d1.push_back(a[i]);
        } else {
            d2.push_back(a[i]);
        }
    }
 
    int res = 0;
    res++;
    for(int i = 2; i < d1.size(); ++i) {
        if(d1[i - 1] != d1[i]) res++;
    }
    if(d1.size() == 1) res--;
    res++;
    for(int i = 2; i < d2.size(); ++i) {
        if(d2[i - 1] != d2[i]) res++;
    }
    if(d2.size() == 1) res--;
 
    cout << res;
 
    return 0;
}
