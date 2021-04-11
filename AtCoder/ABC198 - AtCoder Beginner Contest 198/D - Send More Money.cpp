#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
char s1[21], s2[21], s3[21];
int s1l, s2l, s3l;
bool has[30];
int alNum;

int num[30];
bool isFirst[30];
bool used[10];

vector<int> alpha;
bool finish;

bool ck()
{
    ll n1 = 0;
    ll n2 = 0;
    ll n3 = 0;
    for(int i = 0; i < s1l; ++i) {
        n1 *= 10;
        int ch = s1[i] - 'a';
        n1 += num[ch];
    }
    for(int i = 0; i < s2l; ++i) {
        n2 *= 10;
        int ch = s2[i] - 'a';
        n2 += num[ch];
    }
    for(int i = 0; i < s3l; ++i) {
        n3 *= 10;
        int ch = s3[i] - 'a';
        n3 += num[ch];
    }
    if(n1 + n2 == n3) {
        cout << n1 << "\n";
        cout << n2 << "\n";
        cout << n3 << "\n";
        return true;
    } else return false;
}

void bt(int idx)
{
    if(idx == alpha.size()) {
        if(ck() == true) {
            finish = true;
        }
        return;
    }

    int st = 0;
    if(isFirst[alpha[idx]] == true) st = 1;
    for(int i = st; i <= 9; ++i) {
        if(used[i] == true) continue;
        used[i] = true;
        num[alpha[idx]] = i;
        bt(idx + 1);
        used[i] = false;
        if(finish == true) return;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 30; ++i) {
        num[i] = -1;
    }


    for(int i = 0; i < 26; ++i) {

    }

    cin >> s1 >> s2 >> s3;
    s1l = strlen(s1);
    s2l = strlen(s2);
    s3l = strlen(s3);
    for(int i = 0; i < s1l; ++i) {
        int c = s1[i] - 'a';
        if(has[c] == false) {
            alNum++;
            alpha.push_back(c);
            if(i == 0) isFirst[c] = true;
        }
        has[c] = true;
    }
    for(int i = 0; i < s2l; ++i) {
        int c = s2[i] - 'a';
        if(has[c] == false) {
            alNum++;
            alpha.push_back(c);
            if(i == 0) isFirst[c] = true;
        }
        has[c] = true;
    }
    for(int i = 0; i < s3l; ++i) {
        int c = s3[i] - 'a';
        if(has[c] == false) {
            alNum++;
            alpha.push_back(c);
            if(i == 0) isFirst[c] = true;
        }
        has[c] = true;
    }

    bool pos = false;
    if(alNum <= 10) {
        bt(0);
        if(finish == true) pos = true;
    }

    if(pos == false) {
        cout << "UNSOLVABLE";
    }

    return 0;
}
