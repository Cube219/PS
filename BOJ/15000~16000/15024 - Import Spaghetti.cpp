#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long int;
constexpr int INF = 98765432;

int n;
unordered_map<string, int> str2int;
vector<string> int2str;
int g[501][501], rec[501][501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int2str.resize(n);
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        str2int.insert({ str, i });
        int2str[i] = str;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            g[i][j] = INF;
        }
    }
    for(int i = 0; i < n; ++i) {
        string dststr, tmp;
        int num;
        cin >> dststr >> num;
        getline(cin, tmp);
        int dst = str2int[dststr];
        for(int j = 0; j < num; ++j) {
            getline(cin, tmp);
            int k = 0;
            for(; k < tmp.size(); ++k) {
                if(tmp[k] == ' ') {
                    k++;
                    break;
                }
            }
            string srcstr;
            for(; k < tmp.size(); ++k) {
                if(tmp[k] == ',') {
                    int src = str2int[srcstr];
                    g[dst][src] = 1;
                    rec[dst][src] = src;
                    srcstr.clear();
                    k++;
                } else {
                    srcstr.push_back(tmp[k]);
                }
            }
            int src = str2int[srcstr];
            g[dst][src] = 1;
            rec[dst][src] = src;
        }
    }

    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                    rec[i][j] = rec[i][k];
                }
            }
        }
    }

    vector<int> path;
    int minv = INF;
    for(int i = 0; i < n; ++i) {
        if(g[i][i] < minv) {
            minv = g[i][i];
            path.clear();
            int cur = rec[i][i];
            path.push_back(i);
            while(cur != i) {
                path.push_back(cur);
                cur = rec[cur][i];
            }
        }
    }

    if(minv == INF) {
        cout << "SHIP IT";
    } else {
        for(int i = 0; i < path.size(); ++i) {
            cout << int2str[path[i]] << " ";
        }
    }

    return 0;
}
