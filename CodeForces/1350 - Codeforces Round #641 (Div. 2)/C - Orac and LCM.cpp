#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
using namespace std;

int prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449 };
constexpr int P_NUM = sizeof(prime) / sizeof(int);

int firstMin[P_NUM], secondMin[P_NUM], firstMinCount[P_NUM], secondMinCount[P_NUM];

vector<int> extPrimes;
vector<int> extPrimesNum;

int n, a[100001];
int pNum[P_NUM];
vector<int> extP;

void getPrimes(int a)
{
    for(int i = 0; i < P_NUM; i++) pNum[i] = 0;
    extP.clear();

    int i = 0;
    while(a != 1) {
        if(a % prime[i] == 0) {
            pNum[i]++;
            a /= prime[i];
        } else {
            i++;
            if(i == P_NUM) {
                extP.push_back(a);
                break;
            }
        }
    }
}

long long int pow(int a, int b)
{
    long long int res = 1;
    for(int i = 0; i < b; i++) {
        res *= a;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    for(int i = 0; i < P_NUM; i++) {
        firstMin[i] = secondMin[i] = 2147483647;
    }

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++) {
        getPrimes(a[i]);

        if(extP.size() > 0) {
            for(auto ep : extP) {
                int extSize = extPrimes.size();
                bool isFind = false;
                for(int i = 0; i < extSize; i++) {
                    if(extPrimes[i] == ep) {
                        extPrimesNum[i]++;
                        isFind = true;
                        break;
                    }
                }

                if(isFind == false) {
                    extPrimes.push_back(ep);
                    extPrimesNum.push_back(1);
                }
            }
        }

        for(int i = 0; i < P_NUM; i++) {
            if(pNum[i] < firstMin[i]) {
                firstMinCount[i]++;
                secondMin[i] = firstMin[i];
                firstMin[i] = pNum[i];
            }
            else if(pNum[i] < secondMin[i]) {
                secondMin[i] = pNum[i];
            }
        }
    }

    long long int res = 1;
    for(int i = 0; i < P_NUM; i++) {
        res *= pow(prime[i], secondMin[i]);
    }
    int tt = extPrimes.size();
    for(int i = 0; i < tt; i++) {
        if(extPrimesNum[i] >= n - 1) {
            res *= extPrimes[i];
        }
    }
    printf("%lld", res);

    return 0;
}
