#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin>>n;
    int a, b, c;

    auto p = [&]()
    {
        for(int i = 0; i < n * 4 + 2; ++i)
        {
            if (i == a || i == b || i == c)
            {
                cout<<"*";
            }
            else
            {
                cout<<" ";
            }
        }
        cout<<"\n";
    };

    a = n * 2 - 1;
    b = a + n + 1;
    c = b + 2;
    for (int i = 0; i < n; ++i)
    {
        p();
        a--;
        b--;
        c++;
    }
    b++;
    c--;
    for(int i = 0; i < n; ++i)
    {
        p();
        a--;
        b++;
        c--;
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
