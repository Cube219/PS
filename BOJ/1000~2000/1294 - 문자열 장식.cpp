#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <functional>
using namespace std;

using ll = long long int;

priority_queue<string, vector<string>, greater<string>> pq;
int n;
string res;
int sz;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        sz += str.size();
        str.push_back(126);
        pq.push(std::move(str));
    }

    for(int i = 0; i < sz; ++i) {
        string str = pq.top();
        pq.pop();
        res.push_back(str[0]);
        if(str.size() > 0) {
            string str2 = str.substr(1);
            pq.push(std::move(str2));
        }
    }
    cout << res;

    return 0;
}
