#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <queue>

int n;
int a[100001];
int d[100001];
int currentMex;
bool isPossible = true;

std::queue<int> minus;

int main(void)
{
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++) {
        if(currentMex > a[i]) {
            isPossible = false;
            break;
        } else if(currentMex < a[i]) {
            d[i] = currentMex;
            currentMex++;
            while(currentMex < a[i]) {
                if(minus.empty() == true) {
                    isPossible = false;
                    break;
                }

                int minusIdx = minus.front();
                minus.pop();

                d[minusIdx] = currentMex;
                currentMex++;
            }

            if(isPossible == false) break;
        } else { // currentMex == a[i]
            d[i] = -1;
            minus.push(i);
        }
    }

    if(isPossible == false) {
        printf("-1");
    } else {
        int current = a[n - 1] + 1;
        for(int i = 0; i < n; i++) {
            if(d[i] == -1) {
                d[i] = current;
                current++;
            }
        }

        for(int i = 0; i < n; i++) printf("%d ", d[i]);
    }

    return 0;
}
