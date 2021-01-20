#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <set>
using namespace std;

using lli = long long int;

int n;
set<int> low, high, fire, light;
int lightNum;
lli lowSum, highSum;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;

        if(a == 0) { // Fire
            if(b > 0) {
                fire.insert(b);

                if(high.empty() == false && *high.begin() < b) {
                    int mv = *high.begin();
                    low.insert(mv);
                    high.erase(mv);
                    lowSum += (lli)mv;
                    highSum -= (lli)mv;

                    high.insert(b);
                    highSum += (lli)b;
                } else {
                    low.insert(b);
                    lowSum += (lli)b;
                }
            } else {
                b = -b;
                fire.erase(b);

                if(high.find(b) != high.end()) {
                    high.erase(b);
                    highSum -= (lli)b;

                    int mv = *low.rbegin();
                    low.erase(mv);
                    lowSum -= (lli)mv;
                    high.insert(mv);
                    highSum += (lli)mv;
                } else {
                    low.erase(b);
                    lowSum -= (lli)b;
                }
            }
        } else { // Light
            if(b > 0) {
                light.insert(b);
                lightNum++;

                high.insert(b);
                highSum += (lli)b;
                
                if(low.empty() == false && *low.rbegin() > * high.begin()) {
                    int mv1 = *high.begin();
                    int mv2 = *low.rbegin();

                    high.erase(mv1);
                    highSum -= (lli)mv1;
                    low.insert(mv1);
                    lowSum += (lli)mv1;

                    low.erase(mv2);
                    lowSum -= (lli)mv2;
                    high.insert(mv2);
                    highSum += (lli)mv2;
                }
            } else {
                b = -b;

                light.erase(b);
                lightNum--;

                if(high.find(b) != high.end()) {
                    high.erase(b);
                    highSum -= (lli)b;
                } else {
                    low.erase(b);
                    lowSum -= (lli)b;

                    int mv = *high.begin();
                    high.erase(mv);
                    highSum -= (lli)mv;
                    low.insert(mv);
                    lowSum += (lli)mv;
                }
            }
        }
        lli res = lowSum + (highSum * 2);
        if(light.size() > 0) {
            if(fire.size() == 0) {
                res -= *light.begin();
            } else if(*light.begin() > * fire.rbegin()) {
                res -= *light.begin();
                res += *fire.rbegin();
            }
        }

        cout << res << "\n";
    }

    return 0;
}
