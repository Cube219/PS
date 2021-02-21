#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;

using ll = long long int;

int n, m;
map<string, int> table;
string rTable[101];
vector<int> rg[101];
vector<int> g[101];
vector<int> res;

int scc[101], sNum;
vector<int> sccList[101];
vector<int> st;
int d[101], dNum = 1;
bool finish[101];

int in[101];
bool has[101];

void init()
{
    table.clear();
    st.clear();
    res.clear();
    n = 0;

    for(int i = 0; i < m; ++i) {
        g[i].clear();
        rg[i].clear();
        sccList[i].clear();
        scc[i] = 0;
        d[i] = 0;
        finish[i] = false;
        has[i] = false;

        in[i] = 0;
    }
    sNum = 0;
    dNum = 1;
}

int getNum(const string& str)
{
    auto it = table.find(str);
    if(it == table.end()) {
        table.insert({ str, n });
        rTable[n] = str;
        n++;
        return n - 1;
    }
    return it->second;
}

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        while(1) {
            int top = st.back();
            st.pop_back();

            scc[top] = sNum;
            sccList[sNum].push_back(top);
            finish[top] = true;
            if(top == cur) break;
        }
        sNum++;
    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> m;
        if(m == 0) break;
        init();
        string strLine;
        getline(cin, strLine);
        for(int i = 0; i < m; ++i) {
            getline(cin, strLine);

            vector<string> strs;
            int st = 0;
            for(int j = 0; j <= strLine.size(); ++j) {
                if(strLine[j] == ' ' || strLine[j] == '\0') {
                    strs.push_back(strLine.substr(st, j - st));
                    st = j + 1;
                }
            }

            int a = getNum(strs[0]);
            for(int j = 1; j < strs.size(); ++j) {
                int b = getNum(strs[j]);
                g[b].push_back(a);
                rg[a].push_back(b);
            }
        }

        for(int i = 0; i < n; ++i) {
            if(finish[i] == false) dfs(i);
        }

        for(int i = 0; i < n; ++i) {
            for(int j : g[i]) {
                int sa = scc[i];
                int sb = scc[j];
                if(sa == sb) continue;
                // g2[sa].push_back(sb);
                in[sb]++;
            }
        }

        for(int i = 0; i < sNum; ++i) {
            if(in[i] == 0 || sccList[i].size() > 1 || in[i] < sccList[i].size()) {
                for(int j : sccList[i]) {
                    res.push_back(j);
                    has[j] = true;
                }
            }
        }

        for(int i = 0; i < res.size(); ++i) {
            for(int j : rg[res[i]]) {
                if(has[j] == false) {
                    has[j] = true;
                    res.push_back(j);
                }
            }
        }

        vector<string> res2(res.size());
        for(int i = 0; i < res.size(); ++i) {
            res2[i] = rTable[res[i]];
        }
        sort(res2.begin(), res2.end());
        cout << res2.size() << "\n";
        for(int i = 0; i < res2.size(); ++i) {
            cout << res2[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
