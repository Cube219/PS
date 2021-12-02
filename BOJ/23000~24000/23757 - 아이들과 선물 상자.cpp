#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    priority_queue<int> pq;
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        pq.push(v);
    }
    vector<int> d(m);
    for(auto& v : d) cin >> v;

    int res = 1;
    for(int i = 0; i < m; ++i) {
        if(pq.top() < d[i]) {
            res = 0;
            break;
        }
        int nv = pq.top() - d[i];
        pq.pop();
        pq.push(nv);
    }

    cout << res;

    return 0;
}
