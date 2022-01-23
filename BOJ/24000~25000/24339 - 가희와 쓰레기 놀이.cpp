#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    map<int, int> objCvt;
    int objid = 0;
    struct Obj
    {
        bool isRt;
        bool isLive;
        int id;
    };
    vector<Obj> obj;

    map<int, int> edgeCvt;
    struct Edge
    {
        int src, dst;
        bool isStrong;
        int id;
    };
    vector<Edge> edge;

    int o, e;
    cin >> o >> e;
    for(int i = 0; i < o; ++i) {
        int id;
        string str;
        cin >> id >> str;
        objCvt.insert({id, obj.size()});
        if(str[0] == 'R')
            obj.push_back({true, true, id});
        else
            obj.push_back({false, true, id});
    }

    vector<set<int>> g(obj.size());

    auto bfs = [&](bool isStrong) -> int {
        queue<int> q;
        vector<char> isLive(obj.size(), false);

        for(int i = 0; i < obj.size(); ++i) {
            if(obj[i].isLive == false || obj[i].isRt == false)
                continue;

            q.push(i);
            isLive[i] = true;
        }

        while(q.empty() == false) {
            int cur = q.front();
            q.pop();

            for(auto& nx : g[cur]) {
                Edge eg = edge[nx];
                if(isStrong && eg.isStrong == false)
                    continue;
                if(isLive[eg.dst] == true || obj[eg.dst].isLive == false)
                    continue;
                isLive[eg.dst] = true;
                q.push(eg.dst);
            }
        }

        int res = 0;
        for(int i = 0; i < isLive.size(); ++i) {
            if(isLive[i])
                res++;
            else {
                obj[i].isLive = false;
                objCvt.erase(obj[i].id);
            }
        }
        for(int i = 0; i < edge.size(); ++i) {
            Edge eg = edge[i];
            if(isLive[eg.src] == false || isLive[eg.dst] == false) {
                if(g[eg.src].find(i) != g[eg.src].end()) {
                    edgeCvt.erase(eg.id);
                    g[eg.src].erase(i);
                }
            }
        }
        return res;
    };

    for(int i = 0; i < e; ++i) {
        string op;
        cin >> op;
        if(op == "M") {
            cout << bfs(true) << "\n";
        } else if(op == "m") {
            cout << bfs(false) << "\n";
        } else if(op == "MADE") {
            int id;
            string str;
            cin >> id >> str;
            objCvt.insert({id, obj.size()});
            if(str == "ROOT")
                obj.push_back({true, true, id});
            else
                obj.push_back({false, true, id});
            g.emplace_back();
        } else if(op == "ADD") {
            int eid, o1, o2;
            string dir;
            cin >> eid >> o1 >> dir >> o2;
            edgeCvt.insert({eid, edge.size()});
            o1 = objCvt[o1];
            o2 = objCvt[o2];
            if(dir == "->") {
                g[o1].insert(edge.size());
                edge.push_back({o1, o2, false, eid});
            } else {
                g[o1].insert(edge.size());
                edge.push_back({o1, o2, true, eid});
            }
        } else { // REMOVE
            int eid;
            cin >> eid;
            
            int e = edgeCvt[eid];
            Edge eg = edge[e];
            g[eg.src].erase(e);

            edgeCvt.erase(eid);
        }
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
