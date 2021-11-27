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
    ll v;
    int op;
};

string str;
string cur;

void ck()
{
    if(cur.size() == str.size()) return;

    // valid check
    int cnt = 0;
    bool f = false;
    for(char ch : cur) {
        if('0' <= ch && ch <= '9') {
            if(ch == '0') {
                if(cnt == 0) f = true;
            }
            if(cnt >= 1 && f == true) return;
            cnt++;
        } else {
            f = false;
            cnt = 0;
        }
    }
    // cout << cur << "\n";
    // calculate
    ll num = 0;
    vector<Node> st;
    for(char ch : cur) {
        if('0' <= ch && ch <= '9') {
            num *= 10;
            num += ch - '0';
        } else {
            while(st.size() > 0 && st.back().op == 1) {
                st.pop_back();
                ll lhs = st.back().v;
                st.pop_back();
                num = lhs * num;
            }
            st.push_back({ num, -1 });
            num = 0;
            if(ch == '*') {
                st.push_back({ 0, 1 });
            } else if(ch == '+') {
                st.push_back({ 0, 2 });
            } else { // '-'
                st.push_back({ 0, 3 });
            }
        }
    }
    while(st.size() > 0 && st.back().op == 1) {
        st.pop_back();
        ll lhs = st.back().v;
        st.pop_back();
        num = lhs * num;
    }
    st.push_back({ num, -1 });

    ll res = st[0].v;
    for(int i = 1; i < st.size(); i += 2) {
        if(st[i].op == 2) {
            res = res + st[i + 1].v;
        } else {
            res = res - st[i + 1].v;
        }
    }
    if(res == 2000) {
        cout << cur << "\n";
    }
}

void bt(int idx)
{
    if(idx == str.size()) {
        ck();
        return;
    }
    // *
    cur.push_back('*');
    cur.push_back(str[idx]);
    bt(idx + 1);
    cur.pop_back();
    cur.pop_back();
    // +
    cur.push_back('+');
    cur.push_back(str[idx]);
    bt(idx + 1);
    cur.pop_back();
    cur.pop_back();
    // -
    cur.push_back('-');
    cur.push_back(str[idx]);
    bt(idx + 1);
    cur.pop_back();
    cur.pop_back();
    // empty
    cur.push_back(str[idx]);
    bt(idx + 1);
    cur.pop_back();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    cur.push_back(str[0]);
    bt(1);

    cur = "2100-0+100";
    ck();

    return 0;
}
