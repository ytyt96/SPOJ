#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXLEN 50010

char st[MAXLEN];

int SA[MAXLEN], RA[MAXLEN], tempSA[MAXLEN], tempRA[MAXLEN], counting[MAXLEN];
int n;

void countingSort(int k){
    int maxRange = max(260, n);
    memset(counting, 0, sizeof counting);
    for (int i = 0; i < n; i++)
        counting[i + k < n ? RA[i + k] : 0]++;

    int sum = 0;
    for (int i = 0; i < maxRange; i++){
        int temp = counting[i];
        counting[i] = sum;
        sum += temp;
    }

    for (int i = 0 ; i < n; i++)
        tempSA[counting[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (int i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void constructSA(){
    for (int i = 0; i < n; i++){
        SA[i] = i;
        RA[i] = st[i];
    }

    for (int k = 1; k < n; k <<= 1){
        countingSort(k);
        countingSort(0);
        int rank;
        tempRA[SA[0]] = rank = 0;
        for (int i = 1; i < n; i++)
            tempRA[SA[i]] = (RA[SA[i - 1]] == RA[SA[i]] && RA[SA[i - 1] + k] == RA[SA[i] + k]) ? rank : ++rank;
        for (int i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break;
    }
}

int LCP[MAXLEN], PLCP[MAXLEN], Phi[MAXLEN];

void computeLCP(){
    Phi[SA[0]] = -1;
    for (int i = 1; i < n; i++)
        Phi[SA[i]] = SA[i - 1];
    int L = 0;
    for (int i = 0; i < n; i++){
        if (Phi[i] == -1){
            PLCP[i] = 0;
            continue;
        }
        while (st[i + L] == st[Phi[i] + L])
            L++;
        PLCP[i] = L;
        L = max(L - 1, 0);
    }
    for (int i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}

int main(){
    int T;
    scanf("%d\n", &T);
    while (T--){
        scanf(" %[^\n]", st);
        n = strlen(st);
        st[n++] = '$';
        constructSA();

        computeLCP(); 
        int substring = 0;
        for (int i = 0; i < n; i++){
            substring += n - SA[i] - 1;
            substring -= LCP[i];
        }
        printf("%d\n", substring);
    }
    return 0;
}
