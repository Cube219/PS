#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int tNum;
vector<string> d;
int n;

int dis(string& l, string& r)
{
    int res = 0;
    for(int i = 0; i < 4; i++) {
        if(l[i] != r[i]) res++;
    }
    return res;
}

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        d.clear();
        d.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }

        if(n > 50) {
            cout << "0\n";
            continue;
        }

        res = 987654321;

        for(int i = 0; i < n - 2; i++) {
            for(int j = i + 1; j < n - 1; j++) {
                for(int k = j + 1; k < n; k++) {
                    int t = dis(d[i], d[j]);
                    t += dis(d[i], d[k]);
                    t += dis(d[j], d[k]);

                    if(res > t) res = t;
                }
            }
        }

        cout << res << endl;
    }

    return 0;
}
