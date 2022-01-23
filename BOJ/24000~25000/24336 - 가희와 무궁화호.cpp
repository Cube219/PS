#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iomanip>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve() {
    unordered_map<string, int> cvt;
    cvt["Seoul"] = 1;
    cvt["Yeongdeungpo"] = 2;
    cvt["Anyang"] = 3;
    cvt["Suwon"] = 4;
    cvt["Osan"] = 5;
    cvt["Seojeongri"] = 6;
    cvt["Pyeongtaek"] = 7;
    cvt["Seonghwan"] = 8;
    cvt["Cheonan"] = 9;
    cvt["Sojeongni"] = 10;
    cvt["Jeonui"] = 11;
    cvt["Jochiwon"] = 12;
    cvt["Bugang"] = 13;
    cvt["Sintanjin"] = 14;
    cvt["Daejeon"] = 15;
    cvt["Okcheon"] = 16;
    cvt["Iwon"] = 17;
    cvt["Jitan"] = 18;
    cvt["Simcheon"] = 19;
    cvt["Gakgye"] = 20;
    cvt["Yeongdong"] = 21;
    cvt["Hwanggan"] = 22;
    cvt["Chupungnyeong"] = 23;
    cvt["Gimcheon"] = 24;
    cvt["Gumi"] = 25;
    cvt["Sagok"] = 26;
    cvt["Yangmok"] = 27;
    cvt["Waegwan"] = 28;
    cvt["Sindong"] = 29;
    cvt["Daegu"] = 30;
    cvt["Dongdaegu"] = 31;
    cvt["Gyeongsan"] = 32;
    cvt["Namseonghyeon"] = 33;
    cvt["Cheongdo"] = 34;
    cvt["Sangdong"] = 35;
    cvt["Miryang"] = 36;
    cvt["Samnangjin"] = 37;
    cvt["Wondong"] = 38;
    cvt["Mulgeum"] = 39;
    cvt["Hwamyeong"] = 40;
    cvt["Gupo"] = 41;
    cvt["Sasang"] = 42;
    cvt["Busan"] = 43;

    vector<double> pos(44, 0);
    pos[1] = 0.0;
    pos[2] = 9.1;
    pos[3] = 23.9;
    pos[4] = 41.5;
    pos[5] = 56.5;
    pos[6] = 66.5;
    pos[7] = 75.0;
    pos[8] = 84.4;
    pos[9] = 96.6;
    pos[10] = 107.4;
    pos[11] = 114.9;
    pos[12] = 129.3;
    pos[13] = 139.8;
    pos[14] = 151.9;
    pos[15] = 166.3;
    pos[16] = 182.5;
    pos[17] = 190.8;
    pos[18] = 196.4;
    pos[19] = 200.8;
    pos[20] = 204.6;
    pos[21] = 211.6;
    pos[22] = 226.2;
    pos[23] = 234.7;
    pos[24] = 253.8;
    pos[25] = 276.7;
    pos[26] = 281.3;
    pos[27] = 289.5;
    pos[28] = 296.0;
    pos[29] = 305.9;
    pos[30] = 323.1;
    pos[31] = 326.3;
    pos[32] = 338.6;
    pos[33] = 353.1;
    pos[34] = 361.8;
    pos[35] = 372.2;
    pos[36] = 381.6;
    pos[37] = 394.1;
    pos[38] = 403.2;
    pos[39] = 412.4;
    pos[40] = 421.8;
    pos[41] = 425.2;
    pos[42] = 430.3;
    pos[43] = 441.7;

    auto getmin = [](int h, int m) { return h * 60 + m; };
    auto getdt = [](int t1, int t2) {
        if(t1 > t2) {
            t2 += 24 * 60;
        }
        return t2 - t1;
    };

    int n,
         q;
    cin >> n >> q;
    struct Node {
        int num, st, ed;
    };
    vector<Node> d(n);
    for(int i = 0; i < n; ++i) {
        string name, st, ed;
        cin >> name >> st >> ed;
        d[i].num = cvt[name];

        if(st[0] == '-') d[i].st = -1;
        else {
            int h = (st[0] - '0') * 10 + (st[1] - '0');
            int m = (st[3] - '0') * 10 + (st[4] - '0');
            d[i].st = getmin(h, m);
        }
        if(ed[0] == '-') d[i].ed = -1;
        else {
            int h = (ed[0] - '0') * 10 + (ed[1] - '0');
            int m = (ed[3] - '0') * 10 + (ed[4] - '0');
            d[i].ed = getmin(h, m);
        }
    }

    for(int i = 0; i < q; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int src = cvt[s1];
        int dst = cvt[s2];
        double len = pos[dst] - pos[src];

        double time = 0;
        int cur = -1;
        for(int j = 0; j < n; ++j) {
            if(d[j].num == src) {
                cur = j;
            } else if(d[j].num == dst) {
                time += getdt(d[j - 1].ed, d[j].st);
                break;
            } else if(cur != -1) {
                time += getdt(d[j - 1].ed, d[j].st);
                time += getdt(d[j].st, d[j].ed);
            }
        }

        time /= 60;
        len /= time;
        if(len < 0)
            len = -len;
        cout << fixed << setprecision(15) << len << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
