#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

vector<vector<pair<int, int>>> adjTable;
vector<vector<int>> dfs_num;

int trap = 0;

int iteration = 0;

void DFS(int r, int c){
    dfs_num[r][c] = iteration;
    
    int u = adjTable[r][c].first, v = adjTable[r][c].second;
    if (dfs_num[u][v] == iteration)
        trap++;
    else if (dfs_num[u][v] == -1)
        DFS(u, v);
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    adjTable.assign(n, vector<pair<int, int>>(m));
    dfs_num.assign(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            char ch;
            scanf(" %c ", &ch);
            if (ch == 'N')
                adjTable[i][j] = {i - 1, j};
            else if (ch == 'S')
                adjTable[i][j] = {i + 1, j};
            else if (ch == 'W')
                adjTable[i][j] = {i, j - 1};
            else
                adjTable[i][j] = {i, j + 1};
        }
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (dfs_num[i][j] == -1){
                DFS(i, j);
                iteration++;
            }
            
    printf("%d\n", trap);
}
