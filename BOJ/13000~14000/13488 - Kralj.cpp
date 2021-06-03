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

int n;
int st[500001], d[500001], cnt[500001];
bool has[500001];
vector<int> d2[500001];
multiset<int> m;
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> st[i];
        st[i]--;
        cnt[st[i]]++;
        has[st[i]] = true;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 0; i < n; ++i) {
        int dd;
        cin >> dd;
        d2[st[i]].push_back(dd);
    }

    int idx = 0;
    int num = 0;
    for(int i = 0; i < n * 2; ++i) {
        if(num > 0) has[idx] = false;
        num += cnt[idx];
        num--;
        if(num < 0) num = 0;

        idx++;
        if(idx >= n) idx -= n;
    }
    for(int i = 0; i < n; ++i) {
        if(has[i] == true) {
            idx = i;
            break;
        }
    }
    for(int i = 0; i < n * 2; ++i) {
        for(int j = 0; j < d2[idx].size(); ++j) {
            m.insert(d2[idx][j]);
        }
        d2[idx].clear();
        auto it = m.lower_bound(d[idx]);
        if(it == m.end()) {
            if(m.size() > 0) {
                it = m.begin();
            }
        }
        if(m.size() > 0) {
            if(d[idx] < *it) {
                res++;
            }
            m.erase(it);
        }
        idx++;
        if(idx >= n) idx -= n;
    }
    cout << res;

    return 0;
}
