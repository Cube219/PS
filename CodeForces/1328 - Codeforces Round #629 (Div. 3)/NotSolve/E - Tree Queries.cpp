#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> v;
int q[200001];

int main(void)
{
    scanf("%d %d", &n, &m);
    v.resize(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        bool f = false;
        int t = v[a].size();
        vector<int>& vv = v[a];
        for(int j = 0; j < t; j++) {
            if(vv[j] == b) {
                f = true;
                break;
            }
        }
        if(f == false)
            vv.push_back(b);

        vv = v[b];
        t = v[b].size();
        f = false;
        for(int j = 0; j < t; j++) {
            if(vv[j] == a) {
                f = true;
                break;
            }

        }
        if(f == false) {
            vv.push_back(a);
        }
    }

    for(int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        for(int j = 0; j < k; j++) {
            scanf("%d", &q[j]);
        }


    }

    return 0;
}
