#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[100001];
bool isPath[100001];
bool isVisited[100001];
int st, ed;

vector<int> res;

bool f;
void findPath(int c)
{
    if(c == ed) {
        f = true;
        isPath[c] = true;
        return;
    }

    isVisited[c] = true;
    for(auto next : g[c]) {
        if(isVisited[next] == true) continue;

        findPath(next);

        if(f == true) break;
    }

    if(f == true) {
        isPath[c] = true;
    }

    isVisited[c] = false;
}

void p(int node);

void last(int node)
{
    isVisited[node] = true;

    for(auto next : g[node]) {
        if(isVisited[next] == true) continue;

        p(next);
    }
    res.push_back(node);
}

void p(int node)
{
    isVisited[node] = true;

    res.push_back(node);

    int pathNode = -1;
    for(auto next : g[node]) {
        if(isVisited[next] == true) continue;

        if(isPath[next] == true) {
            pathNode = next;
            continue;
        }

        isVisited[next] = true;

        for(auto nnext : g[next]) {
            if(isVisited[nnext] == true) continue;
            // if(nnext == node) continue;

            p(nnext);
        }
        res.push_back(next);
    }

    if(pathNode != -1) {
        if(pathNode != ed) {
            p(pathNode);
        } else {
            last(pathNode);
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> st >> ed;
    isPath[st] = isPath[ed] = true;

    findPath(st);

    f = false;
    for(int i = 1; i <= n; i++) {
        isVisited[i] = false;
    }
    p(st);

    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << "\n";
    }

    return 0;
}
