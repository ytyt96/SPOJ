#include <bits/stdc++.h>

using namespace std;

int N, M, P, limit;

vector<int> pair_left, pair_right, dist_left, dist_right;
vector<vector<int>> adjlist;
vector<bool> visited;

bool BFS() {
    queue<int> q;

    dist_left.assign(N, -1);
    dist_right.assign(M, -1);

    for (int i = 0; i < N; i++) {
        if (pair_left[i] == -1) {
            dist_left[i] = 0;
            q.push(i);
        }
    }

    limit = INT_MAX;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist_left[u] > limit)
            break;

        for (int v : adjlist[u]) {
            if (dist_right[v] == -1) {
                dist_right[v] = dist_left[u] + 1;
                if (pair_right[v] == -1)
                    limit = dist_right[v];
                else {
                    dist_left[pair_right[v]] = dist_right[v] + 1;
                    q.push(pair_right[v]);
                }
            }
        }
    }
    return limit != INT_MAX;
}

bool DFS(int u) {
    for (int v : adjlist[u]) {
        if (!visited[v] && dist_right[pair_right[v]] == dist_left[u] + 1)
            visited[v] = true;
        if (pair_right[v] != -1 && dist_right[v] == limit)
            continue;
        if (pair_right[v] == -1 || DFS(pair_right[v])) {
            pair_right[v] = u;
            pair_left[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d %d", &N, &M, &P);

    pair_left.assign(N, -1);
    pair_right.assign(M, -1);

    adjlist.assign(N, vector<int>());

    for (int i = 0; i < P; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adjlist[u - 1].push_back(v - 1);
    }
    int matching = 0;
    while (BFS()) {
        visited.assign(M, false);
        for (int i = 0; i < N; i++)
            if (pair_left[i] == -1)
                if (DFS(i))
                    matching++;
    }

    printf("%d\n", matching);
    return 0;
}
