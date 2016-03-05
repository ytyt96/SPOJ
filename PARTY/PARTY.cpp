#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct party_type
{
    int cost, fun;
};

void partyWork(int budget, int partyCount)
{
    vector<party_type> party(partyCount);
    for (int i=0; i!=partyCount; ++i)
        cin>> party[i].cost>> party[i].fun;

    vector<int> dp(budget+1,0);
    for (size_t i=0; i<party.size(); ++i)
        for (int j=budget; j>0; --j)
            if (j-party[i].cost>=0)
                dp[j]=max(dp[j],dp[j-party[i].cost]+party[i].fun);
            else
                break;
    int maxFun=0, fee=0;
    for (int i=0; i<=budget; ++i)
    {
        if (maxFun<dp[i])
        {
            maxFun=dp[i];
            fee=i;
        }
    }
    cout<< fee<< " "<< maxFun<< "\n";
}

int main()
{
    int budget, party;
    cin>> budget>> party;
    while (!(budget==0 && party==0))
    {
        partyWork(budget, party);
        cin>> budget>> party;
    }
    return 0;
}
