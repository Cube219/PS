#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <map>
#include <vector>
#include <queue>
using namespace std;

using lli = long long int;

int n, k, m;
int d[100001];
char s[101];
map<int, int> mp;
vector<int> g[100001];
queue<int> q;
int rec[100001];
vector<int> st;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> s;
        for(int j = 0; j < k; j++) {
            d[i] = d[i] << 1;
            if(s[j] == '1') d[i] += 1;
        }
        mp.insert({ d[i], i });
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < k; j++) {
            int adj = d[i] ^ (1 << j);

            auto findIter = mp.find(adj);
            if(findIter != mp.end()) {
                g[i].push_back(findIter->second);
            }
        }
    }

    cin >> m;

    q.push(1);
    rec[1] = -1;
    while(q.empty() == false) {
        int current = q.front();
        q.pop();

        for(auto next : g[current]){
            if(rec[next] != 0) continue;

            rec[next] = current;
            q.push(next);
        }
    }

    for(int i = 0; i < m; i++) {
        int end;
        cin >> end;

        if(rec[end] == 0) {
            cout << "-1\n";
            continue;
        }

        int current = end;
        while(current != -1) {
            st.push_back(current);
            current = rec[current];
        }

        while(st.empty() == false) {
            cout << st.back() << " ";
            st.pop_back();
        }
        st.clear();
        cout << "\n";
    }

    return 0;
}
