#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
        int N;
        scanf("%d", &N);
        vector<int> vec(N + 1);
        vec[0] = -1;
        for (int i = 0; i < N; i++)
                scanf("%d", &vec[i + 1]);
        vector<int> dp(N + 1);
        dp[0] = 0;
        for (int i = 1; i <= N; i++)
                for (int j = 0; j < i; j++)
                        if (vec[j] < vec[i])
                                if (dp[j] + 1 >= dp[i])
                                        dp[i] = dp[j] + 1;
        int answer = 0;
        for (int i = 0; i <= N; i++)
                if (dp[i] > answer)
                        answer = dp[i];
        printf("%d\n", answer);
}
