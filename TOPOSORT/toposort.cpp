#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<int>> adjList(n);

	vector<int> id(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adjList[x - 1].push_back(y - 1);
		id[y - 1]++;
	}

	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; i++)
		if (id[i] == 0)
			pq.push(i);
	
	vector<int> answer;
	while (!pq.empty()) {
		int u = pq.top();
		pq.pop();
		answer.push_back(u);
		for (int v : adjList[u]) {
			if (--id[v] == 0)
				pq.push(v);
		}
	}
	if (answer.size() == n) {
		printf("%d", answer[0] + 1);
		for (int i = 1; i < answer.size(); i++)
			printf(" %d", answer[i] + 1);
		printf("\n");
	}
	else
		printf("Sandro fails.\n");
}
