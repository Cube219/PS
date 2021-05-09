#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct Node
{
    Node* nxt[26];
    int cnt;
    bool has;
    Node()
    {
        for(int i = 0; i < 26; ++i) {
            nxt[i] = nullptr;
        }
        cnt = 0;
        has = false;
    }
    ~Node()
    {
        for(int i = 0; i < 26; ++i) {
            if(nxt[i] != nullptr) delete nxt[i];
        }
    }

    void insert(const string& str, int idx)
    {
        if(idx == str.size()) {
            has = true;
            return;
        }
        int ch = str[idx] - 'a';
        if(nxt[ch] == nullptr) {
            nxt[ch] = new Node();
            cnt++;
        }
        nxt[ch]->insert(str, idx + 1);
    }
    int process(const string& str, int idx)
    {
        if(idx == str.size()) return 0;
        int ch = str[idx] - 'a';

        int ret = nxt[ch]->process(str, idx + 1);
        if(cnt > 1 || has == true) ret++;
        return ret;
    }
};

Node* root;
int tNum;
int n;
vector<string> d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.precision(2);

    while(1) {
        root = new Node();
        root->has = true;

        cin >> n;
        if(cin.eof() == true) break;
        d.resize(n);
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            root->insert(d[i], 0);
        }
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            cnt += root->process(d[i], 0);
        }
        cout << fixed << (double)cnt / n << "\n";

        delete root;
    }

    return 0;
}
