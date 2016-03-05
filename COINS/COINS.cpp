#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<long long, long long> memo;

long long dp(long long n){
    long long& cell = memo[n];
    if (cell > 0)
        return cell;
    if (n == 0)
        return 0;
    long long split = dp(n / 2) + dp(n / 3) + dp(n / 4);
    cell = max(split, n);
    return cell;
}

int main(){
    long long n = 0;
    while (scanf("%lld", &n) == 1){
        printf("%lld\n", dp(n));
    }
}