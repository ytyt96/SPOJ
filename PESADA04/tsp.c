#include <stdio.h>
#include <string.h>
#include <limits.h>

int next_permutation(unsigned* ptr, int n) {
    unsigned state = *ptr;
    int first = 0;
    while (first + 1 < n && ((state & (1 << (first + 1))) >= (state & (1 << first))))
        first++;

    first++;

    if (first == n)
        return 0;

    int second = first - 1;
    
    state |= (1 << first);
    state ^= (1 << second);

    for (int i = 0; i < (second >> 1); i++) {
        int j = second - 1 - i;
        int bit = (state & (1 << i));
        if (state & (1 << j))
            state |= (1 << i);
        else
            state &= (~(1 << i));
        if (bit)
            state |= (1 << j);
        else
            state &= (~(1 << j));
    }
    *ptr = state;
    return 1;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        if (n == 0) {
            printf("0\n");
            continue;
        }

        n++;
        int adjmat[n][n];
        memset(adjmat, 0, sizeof(adjmat));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    scanf("%d", &adjmat[i][j]);

        int dp[(1 << n)][n];
        memset(dp, 1, sizeof(dp));

        for (int i = 1; i < n; i++) {
            unsigned state = 1;
            state |= (1 << i);
            dp[state][i] = adjmat[0][i];
        }

        for (int i = 3; i <= n; i++) {
            unsigned state = 0;
            for (int j = 0; j < i; j++)
                state |= (1 << j);

            do {
                for (int j = 1; j < n; j++) {
                    if (!(state & (1 << j)))
                        continue;
                    unsigned prev_state = (state ^ (1 << j));

                    for (int k = 1; k < n; k++)
                        if (prev_state & (1 << k))
                            if (dp[prev_state][k] + adjmat[k][j] < dp[state][j])
                                dp[state][j] = dp[prev_state][k] + adjmat[k][j];
                }
            } while (next_permutation(&state, n));
        }

        unsigned final_state = 0;
        for (int i = 0; i < n; i++)
            final_state |= (1 << i);
        int cost = INT_MAX;
        for (int i = 1; i < n; i++)
            if (dp[final_state][i] + adjmat[i][0] < cost)
                cost = dp[final_state][i] + adjmat[i][0];
        printf("%d\n", cost);
    }
}

