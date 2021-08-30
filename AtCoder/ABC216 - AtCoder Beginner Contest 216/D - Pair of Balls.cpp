#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> k[200001];
vector<int> pos[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        k[i].resize(num);
        for(int j = num - 1; j >= 0; --j) {
            int v;
            cin >> v;
            v--;
            k[i][j] = v;
        }
    }

    vector<int> st;
    for(int i = 0; i < m; ++i) {
        int color = k[i].back();
        pos[color].push_back(i);
        if(pos[color].size() == 2) st.push_back(color);
    }

    bool res = true;
    for(int i = 0; i < n; ++i) {
        if(st.empty()) {
            res = false;
            break;
        }
        int color = st.back();
        st.pop_back();

        int p1 = pos[color][0];
        int p2 = pos[color][1];
        pos[color].clear();

        k[p1].pop_back();
        if(k[p1].size() > 0) {
            int nc = k[p1].back();
            pos[nc].push_back(p1);
            if(pos[nc].size() == 2) {
                st.push_back(nc);
            }
        }
        k[p2].pop_back();
        if(k[p2].size() > 0) {
            int nc = k[p2].back();
            pos[nc].push_back(p2);
            if(pos[nc].size() == 2) {
                st.push_back(nc);
            }
        }
    }

    if(res == true) cout << "Yes";
    else cout << "No";

    return 0;
}
