#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

vector<int> g[201];
int a[201], b[201];
bool isComp[201];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

int n;
vector<int> odd, even;

bool ck(ll a, ll b)
{
    if(a < b) swap(a, b);
    if(gcd(a, b) != 1) return false;
    ll c2 = a * a + b * b;
    ll c = sqrt(c2);
    if(c * c != c2) return false;
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if(a % 2 == 0) even.push_back(a);
        else odd.push_back(a);
    }

    for(int i = 0; i < odd.size(); ++i) {
        for(int j = 0; j < even.size(); ++j) {
            if(ck(odd[i], even[j]) == true) {
                g[i].push_back(j);
            }
        }
    }

    // ----- 
    for(int i = 0; i < odd.size(); ++i) {
        a[i] = -1;
    }
    for(int i = 0; i < even.size(); ++i) {
        b[i] = -1;
    }
    int res = 0;
    for(int i = 0; i < odd.size(); ++i) {
        if(a[i] == -1) {
            for(int j = 0; j < odd.size(); ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << res;

    return 0;
}
