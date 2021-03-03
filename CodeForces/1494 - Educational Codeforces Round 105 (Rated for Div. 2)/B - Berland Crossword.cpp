#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int u, r, d, l, n;
int u2, r2, d2, l2;
bool res;

void cp()
{
    u2 = u;
    r2 = r;
    d2 = d;
    l2 = l;
}
void rr1()
{
    u2--;
    r2--;
}
void rr2()
{
    d2--;
    r2--;
}
void rr3()
{
    d2--;
    l2--;
}
void rr4()
{
    u2--;
    l2--;
}

bool ck()
{
    if(u2 < 0 || u2 > n - 2) return false;
    if(r2 < 0 || r2 > n - 2) return false;
    if(d2 < 0 || d2 > n - 2) return false;
    if(l2 < 0 || l2 > n - 2) return false;
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> u >> r >> d >> l;
        res = false;

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    for(int z = 0; z < 2; ++z) {
                        cp();
                        if(i == 1) rr1();
                        if(j == 1) rr2();
                        if(k == 1) rr3();
                        if(z == 1) rr4();

                        if(ck() == true) res = true;
                    }
                }
            }
        }

        if(res == false) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
