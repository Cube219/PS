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
    int n, m;
    cin >> n >> m;

    struct Node
    {
        int par = -1;
    };
    vector<vector<Node>> data(m, vector<Node>(n + 1));
    vector<vector<int>> d(m);
    bool res = true;
    for(int i = 0; i < m; ++i) {
        auto& curData = data[i];

        int num;
        cin >> num;
        d[i].resize(num);
        for(auto& v : d[i]) cin >> v;

        vector<int> st;
        vector<char> has(n + 1, false);
        st.push_back(0);
        for(auto& v : d[i]) {
            if(has[v]) {
                if(st.size() == 1 || st.back() != v) {
                    res = false;
                    break;
                }
                st.pop_back();
                has[v] = false;

                curData[v].par = st.back();
            } else {
                has[v] = true;
                st.push_back(v);
            }
        }
        if(st.size() > 1) {
            res = false;
        }
    }

    // par 연속성
    for(int i = 1; i <= n; ++i) {
        int j = 0;
        int curpar = -1;
        for(; j < m; ++j) {
            if(data[j][i].par != -1) {
                curpar = data[j][i].par;
                j++; break;
            }
        }
        for(; j < m; ++j) {
            if(data[j][i].par != curpar) {
                if(data[j][i].par != -1) {
                    res = false;
                    j = m;
                }
                j++;
                break;
            }
        }

        for(; j < m; ++j) {
            if(data[j][i].par != -1) {
                res = false;
                break;
            }
        }
    }

    // in 연속성
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            int t = 0;
            // 1: i < j / 2: i > j
            for(auto& cur : d) {
                int iIdx = -1, jIdx = -1;
                for(int k = 0; k < cur.size(); ++k) {
                    if(iIdx == -1 && cur[k] == i) iIdx = k;
                    if(jIdx == -1 && cur[k] == j) jIdx = k;
                }

                if(iIdx != -1 && jIdx != -1) {
                    if(iIdx < jIdx) {
                        if(t == 0) t = 1;
                        else if(t == 2) res = false;
                    } else {
                        if(t == 0) t = 2;
                        else if(t == 1) res = false;
                    }
                }
            }
        }
    }

    if(res) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
