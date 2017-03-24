#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int block_size = sqrt(N);
    int block_number = ceil(1.0 * N / block_size);

    vector<int> cows(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &cows[i]);

    vector<vector<int>> blocks(block_number);
    for (int i = 0; i < block_number - 1; i++) {
        blocks[i].reserve(block_size);
        for (int j = 0; j < block_size; j++)
            blocks[i].push_back(cows[i * block_size + j]);
    }
    blocks[block_number - 1].reserve(block_size);
    for (int i = 0; i < N - (block_number - 1) * block_size; i++)
        blocks.back().push_back(cows[(block_number - 1) * block_size + i]);

    for (int i = 0; i < block_number; i++)
        sort(blocks[i].begin(), blocks[i].end());

    while (M--) {
        char op;
        scanf(" %c ", &op);
        if (op == 'M') {
            int i, X;
            scanf("%d %d", &i, &X);
            auto &block = blocks[(i - 1) / block_size];
            auto it = lower_bound(block.begin(), block.end(), cows[i - 1]);
            *it = X;
            cows[i - 1] = X;
            sort(block.begin(), block.end());
        }
        else {
            int P, Q, X;
            scanf("%d %d %d", &P, &Q, &X);
            int answer = 0;
            P--, Q--;
            int start_block = P / block_size, end_block = Q / block_size;
            if (start_block == end_block) {
                for (int i = P; i <= Q; i++)
                    answer += (cows[i] <= X);
            }
            else {
                for (int i = P; i < (start_block + 1) * block_size; i++)
                    answer += (cows[i] <= X);
                for (int i = end_block * block_size; i <= Q; i++)
                    answer += (cows[i] <= X);
                for (int i = start_block + 1; i < end_block; i++) {
                    auto &block = blocks[i];
                    auto it = upper_bound(block.begin(), block.end(), X);
                    answer += it - block.begin();
                }
            }
            printf("%d\n", answer);
        }
    }
    return 0;
}
