#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int Start = 0;
constexpr int Switch = 1;
constexpr int Platform = 2;
struct Node
{
    int type;
    bool status;
    vector<int> nxt;
    char name;

    int train = -1;
    char dst;
    int time;
};

int n, m;
Node d[101];
vector<bool> path[30];
pair<int, char> train[1001];
int curTime;
vector<pair<int, int>> res;

vector<bool> st;
void bt(int cur)
{
    if(d[cur].type == Platform) {
        path[d[cur].name - 'a'] = st;
    }
    for(int i = 0; i < d[cur].nxt.size(); ++i) {
        if(i == 0) st.push_back(false);
        else st.push_back(true);
        bt(d[cur].nxt[i]);
        st.pop_back();
    }
}

void ck()
{
    for(int i = 0; i <= n; ++i) {
        if(d[i].type == Switch && d[i].train != -1) {
            bool p = path[d[i].dst - 'a'][d[i].time];
            if(p != d[i].status) {
                res.push_back({ curTime, i });
                d[i].status = p;
            }
        }
    }
}
Node tmpd[101];
void mv()
{
    for(int i = 0; i <= n; ++i) {
        tmpd[i] = d[i];
        d[i].train = -1;
    }

    for(int i = 0; i <= n; ++i) {
        if(tmpd[i].type == Platform) {
            tmpd[i].train = -1;
        } else {
            int nxt = 0;
            if(tmpd[i].status == false) {
                nxt = tmpd[i].nxt[0];
            } else {
                nxt = tmpd[i].nxt[1];
            }
            d[nxt].train = tmpd[i].train;
            d[nxt].dst = tmpd[i].dst;
            d[nxt].time = tmpd[i].time + 1;
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        char ch;
        int par;
        cin >> ch >> par;
        if(ch == 's') {
            d[i].type = Switch;
            d[i].status = false;
        } else {
            char p;
            cin >> p;
            d[i].type = Platform;
            d[i].name = p;
        }
        d[par].nxt.push_back(i);
    }

    bt(0);

    cin >> m;
    for(int i = 0; i < m; ++i) {
        cin >> train[i].first >> train[i].second;
    }

    int trainIdx = 0;
    for(curTime = 0; curTime < 20000; ++curTime) {
        if(train[trainIdx].first == curTime) {
            d[0].train = trainIdx;
            d[0].time = 0;
            d[0].dst = train[trainIdx].second;
            trainIdx++;
        }
        ck();
        mv();
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].second << " " << res[i].first << "\n";
    }

    return 0;
}
