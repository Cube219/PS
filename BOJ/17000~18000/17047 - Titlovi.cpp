#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int t;
int h, m, s, ms;
struct Time
{
    int num;
    int h, m, s, ms;
    int eh, em, es, ems;
    vector<string> str;
};
Time d[101];
int dNum;
vector<string> buf;

void parse()
{
    for(int i = 0; i < buf[0].size(); ++i) {
        d[dNum].num *= 10;
        d[dNum].num += buf[0][i] - '0';
    }
    d[dNum].h = (buf[1][0] - '0') * 10 + (buf[1][1] - '0');
    d[dNum].m = (buf[1][3] - '0') * 10 + (buf[1][4] - '0');
    d[dNum].s = (buf[1][6] - '0') * 10 + (buf[1][7] - '0');
    d[dNum].ms = (buf[1][9] - '0') * 100 + (buf[1][10] - '0') * 10 + (buf[1][11] - '0');

    d[dNum].eh = (buf[1][17] - '0') * 10 + (buf[1][18] - '0');
    d[dNum].em = (buf[1][20] - '0') * 10 + (buf[1][21] - '0');
    d[dNum].es = (buf[1][23] - '0') * 10 + (buf[1][24] - '0');
    d[dNum].ems = (buf[1][26] - '0') * 100 + (buf[1][27] - '0') * 10 + (buf[1][28] - '0');

    for(int i = 2; i < buf.size() - 1; ++i) {
        d[dNum].str.push_back(buf[i]);
    }
    dNum++;
}
bool finish = false;

void p(Time& node)
{
    while(node.ms >= 1000) {
        node.s++;
        node.ms -= 1000;
    }
    while(node.s >= 60) {
        node.m++;
        node.s -= 60;
    }
    while(node.m >= 60) {
        node.h++;
        node.m -= 60;
    }

    while(node.ms < 0) {
        node.s--;
        node.ms += 1000;
    }
    while(node.s < 0) {
        node.m--;
        node.s += 60;
    }
    while(node.m < 0) {
        node.h--;
        node.m += 60;
    }

    while(node.ems >= 1000) {
        node.es++;
        node.ems -= 1000;
    }
    while(node.es >= 60) {
        node.em++;
        node.es -= 60;
    }
    while(node.em >= 60) {
        node.eh++;
        node.em -= 60;
    }

    while(node.ems < 0) {
        node.es--;
        node.ems += 1000;
    }
    while(node.es < 0) {
        node.em--;
        node.es += 60;
    }
    while(node.em < 0) {
        node.eh--;
        node.em += 60;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        buf.clear();
        while(1) {
            buf.push_back("");
            getline(cin, buf.back());
            if(buf.back().size() == 0 || buf.back()[0] == '#') break;
        }
        parse();
        if(buf.back()[0] == '#') break;
    }
    cin >> t;
    for(int i = 0; i < dNum; ++i) {
        d[i].ms += t;
        d[i].ems += t;
        p(d[i]);
    }

    for(int i = 0; i < dNum; ++i) {
        printf("%d\n", d[i].num);
        printf("%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d\n", d[i].h, d[i].m, d[i].s, d[i].ms, d[i].eh, d[i].em, d[i].es, d[i].ems);
        for(int j = 0; j < d[i].str.size(); ++j) {
            printf("%s\n", d[i].str[j].c_str());
        }
        if(i != dNum - 1) printf("\n");
        else printf("#\n");
    }

    return 0;
}
