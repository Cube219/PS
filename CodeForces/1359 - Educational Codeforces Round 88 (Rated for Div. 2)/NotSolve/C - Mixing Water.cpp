#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <math.h>
#include <float.h>

int tNum;
int h, c, t;
using lli = unsigned long long int;

long double hotMin, coldMin, hotAbs, coldAbs;
long double minAbs;
int res;

long double fa(long double ttt)
{
    if(ttt < 0) return -ttt;
    else return ttt;
}

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d", &h, &c, &t);

        lli sum = 0;
        int count = 0;

        hotMin = 2000001;
        coldMin = 2000001;
        minAbs = 2000000;
        while(1) {
            // Hot
            sum += h;
            count++;
            long double hotCurrent = (long double)sum / (long double)count;
            
            // Cold
            sum += c;
            count++;
            long double coldCurrent = (long double)sum / (long double)count;

            hotAbs = fa(hotCurrent - (long double)t);
            coldAbs = fa(coldCurrent - (long double)t);

            if(minAbs > hotAbs) {
                minAbs = hotAbs;
                res = count - 1;
            }
            if(minAbs > coldAbs) {
                minAbs = coldAbs;
                res = count;
            }
  
            if(minAbs == 0) {
                break;
            }
            if(hotMin > hotAbs) {
                hotMin = hotAbs;
            } else {
                break;
            }

            if(coldCurrent >= (long double)t || hotCurrent < (long double)t) {
                break;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
