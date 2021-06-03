#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

int n;
int d[200001];
multiset<int> st;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    ll sum = 0;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        sum += d[i];
        res++;
        if(d[i] < 0) {
            st.insert(d[i]);
        }
        while(sum < 0) {
            res--;
            auto it = st.begin();
            sum -= *it;
            st.erase(it);
        }
    }
    cout << res;

    return 0;
}
