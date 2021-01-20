#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
using namespace std;

using lli = long long int;

int tNum;
int n;
struct Edge
{
    int a;
    int b;
    int cost;
};
bool operator<(const Edge& l, const Edge& r)
{
    return l.cost < r.cost;
}

Edge egs[510001];
int egNum;
int parent[1001], edgeNum[1001], nodeNum[1001];
set<int> updated;
int res;

int findRoot(int i)
{
    vector<int> toUpdate;

    while(parent[i] != i) {
        toUpdate.push_back(i);
        i = parent[i];
    }

    for(auto it = toUpdate.begin(); it != toUpdate.end(); it++) {
        parent[*it] = i;
    }

    return i;
}

void uni(int a, int b)
{
    int aR = findRoot(a);
    int bR = findRoot(b);

    if(aR == bR) return;
    parent[bR] = aR;
    edgeNum[aR] += edgeNum[bR];
    nodeNum[aR] += nodeNum[bR];
}


int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        egNum = 0;

        cin >> n;
        for(int i = 1; i < n; i++) {
            for(int j = i + 1; j <= n; j++) {
                int c;
                cin >> c;
                egs[egNum++] = { i, j, c };
            }
        }
        sort(egs, egs + egNum);

        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            edgeNum[i] = 0;
            nodeNum[i] = 1;
        }

        for(int ei = 0; ei < egNum;) {
            int cCost = egs[ei].cost;

            while(ei < egNum && cCost == egs[ei].cost) {
                Edge e = egs[ei];
                ei++;

                int aRoot = findRoot(e.a);
                edgeNum[aRoot]++;
                uni(e.a, e.b);
                updated.insert(aRoot);
            }

            for(auto it = updated.begin(); it != updated.end(); it++) {
                int idx = *it;
                if(parent[idx] != idx) continue;

                int unionEdgeNum = edgeNum[idx];
                int unionNodeNum = nodeNum[idx];

                if(unionNodeNum > 1 && unionNodeNum < n && unionNodeNum * (unionNodeNum - 1) == unionEdgeNum * 2) {
                    res++;
                }
            }

            updated.clear();
        }

        cout << res << "\n";
    }

    return 0;
}
