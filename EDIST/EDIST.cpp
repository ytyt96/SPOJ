#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int min(int a, int b)
{
    return a < b? a: b;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        string word1, word2;
        cin >> word1 >> word2;
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, word1.size() + word2.size()));
        dp[0][0] = 0;

        for (int j = 1; j <= word1.size(); ++j)
            dp[j][0] = j;
        for (int j = 1; j <= word2.size(); ++j)
            dp[0][j] = j;

        for (int j = 1; j <= word1.size(); ++j)
            for (int k = 1; k <= word2.size(); ++k)
            {
                if (word1[j - 1] == word2[k - 1])
                    dp[j][k] = dp[j - 1][k - 1];
                dp[j][k] = min(min(dp[j][k], dp[j][k - 1] + 1), min(dp[j - 1][k - 1] + 1, dp[j - 1][k] + 1));
            }
        cout << dp[word1.size()][word2.size()] << "\n";
    }
    return 0;
}
