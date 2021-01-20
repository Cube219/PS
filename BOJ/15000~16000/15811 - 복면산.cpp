#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <string.h>

using lli = long long int;
constexpr int INF = 987654321;

char a[20], b[20], c[20];
int al, bl, cl, maxl;
bool isPossible = false;

bool hasAlphabet[30];
int alphabets[30];
int alphabetsNum;

int usedNum[10];
int usedAlphabet[30];

bool Check()
{
    int carry = 0;
    for(int i = 0; i < maxl; i++) {
        int aNum = 0, bNum = 0, cNum = 0;
        if(i < al) aNum = usedAlphabet[a[i]];
        if(i < bl) bNum = usedAlphabet[b[i]];
        if(i < cl) cNum = usedAlphabet[c[i]];

        if(cNum != ((aNum + bNum + carry) % 10)) {
            return false;
        }

        carry = (aNum + bNum + carry) / 10;
    }

    if(carry == 0) return true;
    else return false;
}

void process(int idx)
{
    if(idx >= alphabetsNum) {
        if(Check() == true) {
            isPossible = true;
        }
        return;
    }

    for(int i = 0; i <= 9; i++) {
        if(usedNum[i] != -1) continue;

        usedAlphabet[alphabets[idx]] = i;
        usedNum[i] = alphabets[idx];

        process(idx + 1);

        usedNum[i] = -1;

        if(isPossible == true) break;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    for(int i = 0; i <= 9; i++) {
        usedNum[i] = -1;
    }

    scanf("%s %s %s", a, b, c);
    al = strlen(a);
    bl = strlen(b);
    cl = strlen(c);
    maxl = al;
    if(maxl < bl) maxl = bl;
    if(maxl < cl) maxl = cl;
    if(al < bl) {
        std::swap(al, bl);
        std::swap(a, b);
    }
    for(int i = 0; i < al / 2; i++) {
        std::swap(a[i], a[al - i - 1]);
    }
    for(int i = 0; i < bl / 2; i++) {
        std::swap(b[i], b[bl - i - 1]);
    }
    for(int i = 0; i < cl / 2; i++) {
        std::swap(c[i], c[cl - i - 1]);
    }

    for(int i = 0; i < al; i++) {
        a[i] -= 'A';
        hasAlphabet[a[i]] = true;
    }
    for(int i = 0; i < bl; i++) {
        b[i] -= 'A';
        hasAlphabet[b[i]] = true;
    }
    for(int i = 0; i < cl; i++) {
        c[i] -= 'A';
        hasAlphabet[c[i]] = true;
    }
    for(int i = 0; i < 'Z' - 'A' + 1; i++) {
        if(hasAlphabet[i] == true) {
            alphabets[alphabetsNum++] = i;
        }
    }

    if(alphabetsNum > 10) {
        isPossible = false;
    } else {
        process(0);
    }
    if(isPossible == true) printf("YES");
    else printf("NO");
                                               
    return 0;
}
