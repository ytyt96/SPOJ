#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int N;
    scanf("%d", &N);
    int pow2[20];
    pow2[0] = 1;
    for (int i = 1; i < 20; i++)
        pow2[i] = pow2[i - 1] * 2;
    int sparse[100500][18];

    int log_2[100500];
    for (int i = 0; i < N; i++)
        log_2[i] = log2(i);

    int A[100500];
    for (int i = 0; i < N; i++){
        scanf("%d", &A[i]);
        sparse[i][0] = A[i];
    }

    for (int j = 1; j < 20; j++)
        for (int i = 0; i < N; i++)
            if (i + pow2[j] - 1 < N)
                sparse[i][j] = min(sparse[i][j - 1], sparse[i + pow2[j - 1]][j - 1]);

    int Q;
    scanf("%d", &Q);
    while (Q--){
        int i, j;
        scanf("%d %d", &i, &j);
        if (i == j)
            printf("%d\n", sparse[i][0]);
        else
            printf("%d\n", min(sparse[i][log_2[j - i]], sparse[j - pow2[log_2[j - i]] + 1][log_2[j - i]]));
        
    }

}
