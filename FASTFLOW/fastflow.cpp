#include <bits/stdc++.h>

using namespace std;

int M, N;
long long max_flow, flow;
int s, t;

vector<vector<long long>> residue;
vector<vector<long long>> adjlist;
vector<int> parent;

void augment(int u, long long min_edge) {
    if (u == s) {
        flow = min_edge;
        return;
    }
    else if (parent[u] != -1) {
        int v = parent[u];
        augment(v, min(min_edge, residue[v][u]));
        residue[v][u] -= flow;
        residue[u][v] += flow;
    }
}

void Dinic() {
    max_flow = 0;
    while (true) {
        parent.assign(N, -1);
        vector<bool> visited(N, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t)
                break;
            for (int v : adjlist[u]) {
                if (!visited[v] && residue[u][v] > 0) {
                    parent[v] = u;
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        long long new_flow = 0;
        for (int u : adjlist[t]) {
            if (residue[u][t] <= 0)
                continue;
            flow = 0;
            augment(u, residue[u][t]);
            residue[u][t] -= flow;
            residue[t][u] += flow;
            new_flow += flow;
        }
        if (new_flow == 0)
            break;
        max_flow += new_flow;
    }
}

int main() {
    scanf("%d %d", &N, &M);
    residue.assign(N, vector<long long>(N, 0));
    adjlist.assign(N, vector<long long>());
    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        if (residue[u - 1][v - 1] == 0)
            adjlist[u - 1].push_back(v - 1);
        if (residue[v - 1][u - 1] == 0)
            adjlist[v - 1].push_back(u - 1);
        residue[u - 1][v - 1] += c;
        residue[v - 1][u - 1] += c;
    }

    s = 0;
    t = N - 1;

    Dinic();
    printf("%lld\n", max_flow);
    return 0;
}
