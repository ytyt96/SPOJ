#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;
 
int N, M, P, limit;

#define MAXN 50500
#define MAXE 150500
 
int pair_left[MAXN], pair_right[MAXN], dist_left[MAXN], dist_right[MAXN];
bool visited[MAXN];

int adjlist[MAXN];
int node[MAXE];
int link[MAXE];

 
bool BFS() {
    queue<int> q;
 
    memset(dist_right, -1, sizeof dist_right);
    memset(dist_left, -1, sizeof dist_left);
 
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
 
        for (int i = adjlist[u]; i != -1; i = link[i]) {
            int v = node[i];
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
    for (int i = adjlist[u]; i != -1; i = link[i]) {
        int v = node[i];
        if (!visited[v] && dist_right[v] == dist_left[u] + 1) {
            visited[v] = true;
            if (pair_right[v] != -1 && dist_right[v] == limit)
                continue;
            if (pair_right[v] == -1 || DFS(pair_right[v])) {
                pair_right[v] = u;
                pair_left[u] = v;
                return true;
            }
        }
    }
    return false;
}
 
int main() {
    scanf("%d %d %d", &N, &M, &P);

    memset(pair_left, -1, sizeof pair_left);
    memset(pair_right, -1, sizeof pair_right);
    memset(link, -1, sizeof link);
    memset(adjlist, -1, sizeof adjlist);
 
    for (int i = 0; i < P; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        node[i] = v - 1;
        link[i] = adjlist[u - 1];
        adjlist[u - 1] = i;
    }
    int matching = 0;
    while (BFS()) {
        memset(visited, 0, sizeof visited);
        for (int i = 0; i < N; i++)
            if (pair_left[i] == -1)
                if (DFS(i))
                    matching++;
    }
    printf("%d\n", matching);
    return 0;
}
