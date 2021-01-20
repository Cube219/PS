#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
#include <utility>

int tNum, n, m;
char s[51];
int b[51];

std::stack<int> st;

char res[51];
bool isFinished[51];

bool isf;

int cusAbs(int a)
{
    if(a < 0) return -a;
    else return a;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%s %d", s, &m);
        n = strlen(s);
        for(int i = 0; i < m; i++) {
            scanf("%d", &b[i]);
            isFinished[i] = false;
        }

        std::sort(s, s + n);

        int currentS = n - 1;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                if(isFinished[j] == false && b[j] == 0) {
                    st.push(j);
                }
            }
            bool isPossible = true;
            for(int j = 1; j < st.size(); j++) {
                if(s[currentS] != s[currentS - j]) {
                    isPossible = false;
                    
                    i--;
                    currentS -= j;  

                    break;
                }
            }
            if(isPossible == true) {
                for(int j = 0; j < m; j++) {
                    if(isFinished[j] == false && b[j] == 0) {
                        isFinished[j] = true;
                    }
                }
                i += st.size() - 1;
                while(st.empty() == false) {
                    int t = st.top();
                    st.pop();

                    for(int j = 0; j < m; j++) {
                        if(isFinished[j] == false) {
                            b[j] -= cusAbs(j - t);
                        }
                    }

                    res[t] = s[currentS];
                    currentS--;
                }
            } else {
                while(st.empty() == false) st.pop();
            }
        }

        res[m] = '\0';

        printf("%s\n", res);
    }

    return 0;
}
