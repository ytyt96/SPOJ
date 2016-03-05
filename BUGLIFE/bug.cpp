#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> adjList;
vector<int> dfs_num, dfs_low, SCC, stack;
vector<bool> visited;

int SCCCounter, nodeCounter;
int N;
bool suspicious;

void TarjanSCC(int u){
    dfs_num[u] = dfs_low[u] = nodeCounter++;
    stack.push_back(u);
    visited[u] = true;

    for (int v : adjList[u]){
        if (dfs_num[v] == -1)
            TarjanSCC(v);
        if (suspicious)
            return;
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]){
        while (true){
            int v = stack.back();
            stack.pop_back();
            visited[v] = false;
            SCC[v] = SCCCounter;
            // Both X and Not X are in the same SCC, the expression is unsatisfiable.
            if (SCC[v] == SCC[v ^ 1]){
                suspicious = true;
                return;
            }
            if (u == v)
                break;
        }
        SCCCounter++;
    }
}

int main(){
    int T;
    scanf("%d", &T);
    for (int caseNo = 0; caseNo < T; caseNo++){
        int M;
        scanf("%d %d", &N, &M);
        N <<= 1;
        
        // Let X be female, Not X be male.
        adjList.assign(N, vector<int>());

        while (M--){
            int b1, b2;
            scanf("%d %d", &b1, &b2);
            b1--, b2--;
            b1 <<= 1;
            b2 <<= 1;
            
            // b1 and b2 must be of opposite gender.
            // That is, (Xb1 or Xb2) and (Not Xb1 or Not Xb2)
            adjList[b1].push_back(b2 ^ 1);
            adjList[b2].push_back(b1 ^ 1);
            adjList[b1 ^ 1].push_back(b2);
            adjList[b2 ^ 1].push_back(b1);
        }

        dfs_num.assign(N, -1);
        dfs_low.assign(N, 0);
        SCC.assign(N, -1);
        SCCCounter = nodeCounter = 0;
        suspicious = false;
        stack.clear();
        visited.assign(N, false);

        // Use Tarjan's algorithm to find SCC
        for (int i = 0; !suspicious && i < N; i++)
            if (dfs_num[i] == -1)
                TarjanSCC(i);

        printf("Scenario #%d:\n", caseNo + 1);
        if (suspicious)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");
    }
}
