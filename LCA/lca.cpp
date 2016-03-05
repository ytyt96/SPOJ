#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct node_t{
    vector<int> child;
    int ancestor = -1;
    int level = -1;
};

vector<node_t> nodes;
int N, logMax;
vector<vector<int>> jump;

void build_level(int root){
    for (int child : nodes[root].child){
        nodes[child].level = nodes[root].level + 1;
        build_level(child);
    }
}

void init_jumpTable(){
    logMax = log2(N);
    jump.assign(nodes.size(), vector<int>(logMax + 1, -1));

    for (int i = 0; i < N; i++)
        jump[i][0] = nodes[i].ancestor;

    for (int j = 1; j <= logMax; j++)
        for (int i = 0; i < N; i++)
            if (jump[i][j - 1] != -1)
                jump[i][j] = jump[jump[i][j - 1]][j - 1];
}

int LCA(int u, int v){
    if (nodes[u].level < nodes[v].level){
        int temp = u;
        u = v;
        v = temp;
    }

    int logVal = log2(nodes[u].level);

    for (int i = logVal; i >= 0; i--)
        if (nodes[u].level - (1 << i) >= nodes[v].level)
            u = jump[u][i];

    if (u == v)
        return u;
    
    for (int i = logVal; i >= 0; i--)
        if (jump[u][i] != -1 && jump[u][i] != jump[v][i]){
            u = jump[u][i];
            v = jump[v][i];
        }
    return nodes[u].ancestor;
}

int main(){
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++){
        printf("Case %d:\n", tc);
        scanf("%d", &N);
        nodes.assign(N, node_t());
        vector<bool> isRoot(N, true);
        for (int i = 0; i < N; i++){
            int M;
            scanf("%d", &M);
            while (M--){
                int node;
                scanf("%d", &node);
                node--;
                nodes[i].child.push_back(node);
                nodes[node].ancestor = i;
                isRoot[node] = false;
            }
        }

        int root;
        for (int i = 0; i < N; i++)
            if (isRoot[i]){
                root = i;
                break;
            }
        nodes[root].level = 0;
        build_level(root);
        init_jumpTable();
        int Q;
        scanf("%d", &Q);
        while (Q--){
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            printf("%d\n", LCA(u, v) + 1);
        }
    }
}
