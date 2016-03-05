#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    //ifstream fin("input.in");
    istream& in(cin);
    string line;
    int case_no = 1;
    while (in >> line && line != "bye")
    {
        vector<int> numbers;
        numbers.push_back(0);
        for (int i = 0; i < line.size(); ++i)
            numbers.push_back(line[i] - '0');
        vector<int> sums;
        sums.push_back(0);
        for (int i = 1; i < numbers.size(); ++i)
            sums.push_back(sums.back() + numbers[i]);
        vector<vector<int>> dp(numbers.size(), vector<int>(250, 0));
        dp[0][0] = 1;

        for (int i = 1; i < numbers.size(); ++i)
            for (int j = 0; j < i; ++j)
                for (int k = 0; k < 250; ++k)
                    if (sums[i] - sums[j] >= k)
                        dp[i][sums[i] - sums[j]] += dp[j][k];


        int result = 0;
        for (int i = 0; i < 250; ++i)
            result += dp[numbers.size() - 1][i];
        cout << case_no++ << ". " << + result << "\n";
    }
    return 0;
}
