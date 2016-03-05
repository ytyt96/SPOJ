#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;


int main(){
	int N;
	scanf("%d", &N);
	vector<int> treats(N);
	for (int i = 0; i < N; i++)
		scanf("%d", &treats[i]);
	vector<vector<long long>> dp(N + 1, vector<long long>(N, 0));
	vector<int> sum(N + 1);
	sum[0] = 0;
	for (int i = 1; i <= N; i++)
		sum[i] = sum[i - 1] + treats[i - 1];

	for (int i = 0; i < N; i++)
		dp[1][i] = treats[i];

	for (int i = 2; i <= N; i++)
		for (int j = 0; j < N; j++){
			if (j + i > N)
				break;
			dp[i][j] = max(treats[j] + dp[i - 1][j + 1] + sum[j + i] - sum[j + 1],
					treats[j + i - 1] + dp[i - 1][j] + sum[j + i - 1] - sum[j]);
		}
	printf("%lld\n", dp[N][0]);
}
