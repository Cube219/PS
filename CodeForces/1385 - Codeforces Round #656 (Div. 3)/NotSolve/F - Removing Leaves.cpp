#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

int tNum;
int n, k;
int leafCount[200001];
bool isLeaf[200001];
vector<int> g[200001];
int childNum[200001];
stack<int> st;

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &k);

        for(int i = 1; i <= n; i++) {
            g[i].clear();
            leafCount[i] = 0;
            isLeaf[i] = false;
            childNum[i] = 0;
        }
        res = 0;

        for(int i = 0; i < n - 1; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            g[a].push_back(b);
            g[b].push_back(a);
        }

        for(int i = 1; i <= n; i++) {
            childNum[i] = g[i].size();
            if(g[i].size() == 1) {
                leafCount[g[i][0]]++;
                isLeaf[i] = true;
            }
        }

        for(int i = 1; i <= n; i++) {
            if(leafCount[i] >= k){
                st.push(i);
            }
        }

        while(st.size() > 0) {
            int node;
            node = st.top();
            st.pop();

            int cutNum = leafCount[node] / k;
            res += cutNum;
            childNum[node] -= cutNum * k;
            if(childNum[node] == 1) {
                for(auto child : g[node]) {
                    if(isLeaf[child] == false) {
                        leafCount[child]++;
                        if(leafCount[child] == k) {
                            st.push(child);
                        }
                    }
                }

                isLeaf[node] = true;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
