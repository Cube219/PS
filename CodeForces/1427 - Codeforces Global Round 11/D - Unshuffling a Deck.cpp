#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int d[101];

struct Area
{
    int st;
    int cnt;
};
vector<Area> v;
int st[101];

vector<vector<int>> res;

void reconstruct()
{
    v.push_back({ d[0], 1 });
    st[d[0]] = 0;
    for(int i = 1; i < n; i++) {
        if(d[i - 1] + 1 == d[i]) {
            v.back().cnt++;
        } else {
            v.push_back({ d[i], 1 });
            st[d[i]] = v.size() - 1;
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }

    reconstruct();

    vector<Area> vt;
    while(v.size() > 1) {
        int idx = st[1];
        int nextIdx;
        while(1) {
            if(v[idx].st + v[idx].cnt > n) break;
            nextIdx = st[v[idx].st + v[idx].cnt];
            if(nextIdx < idx) break;
            idx = nextIdx;
        }

        res.push_back(vector<int>());
        vector<int>& nRes = res.back();

        for(int i = 0; i < v.size(); i++) {
            if(i == nextIdx) {
                int tmp = v[i].cnt;
                i++;
                while(i != idx) {
                    tmp += v[i].cnt;
                    i++;
                }
                i--;
                nRes.push_back(tmp);
            } else {
                nRes.push_back(v[i].cnt);
            }
        }

        vt.clear();

        bool flag = false;
        int stI = 0;
        for(int i = v.size() - 1; i >= 0; i--) {
            if(flag == true) {
                if(i == nextIdx) {
                    vt.back().cnt += v[i].cnt;
                    for(int j = nextIdx + 1; j <= stI; j++) {
                        vt.push_back(v[j]);
                    }
                    flag = false;
                }
            } else {
                vt.push_back(v[i]);
                if(i == idx) {
                    flag = true;
                    stI = i - 1;
                }
            }
        }

        for(int i = vt.size() - 1; i >= 1; i--) {
            if(vt[i - 1].st + vt[i - 1].cnt == vt[i].st) {
                vt[i - 1].cnt += vt[i].cnt;
                vt.erase(vt.begin() + i);
            }
        }
        
        v.clear();
        v.assign(vt.begin(), vt.end());
        vt.clear();

        for(int i = 0; i < v.size(); i++) {
            st[v[i].st] = i;
        }

        // reconstruct();
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) {
        cout << res[i].size() << " ";
        for(int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
