#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> convert(int N, int base){
    vector<int> num(100, 0);
    int index = 0;
    while (N > 0){
        num[index] = N % base;
        N /= base;
        index++;
    }
    return num;
}
int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        int test, B, X, Y;
        scanf("%d %d %d %d", &test, &B, &X, &Y);
        vector<int> X_num = convert(X, B);
        vector<int> Y_num = convert(Y, B);
        int mult = 1, sum = 0;
        for (int i = 0; i < 100; i++){
            int num = X_num[i] + Y_num[i];
            num %= B;
            sum += num * mult;
            mult *= B;
        }
        printf("%d %d\n", test, sum);
    }
}
