#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ret_t{
    int left, right, sum, maxSum, valid;
};

class SegmentTree{
private:
    vector<int> sum, maxSum, leftSum, rightSum, A;
    int n;
    int left(int p) {return p << 1;}
    int right(int p) {return (p << 1) + 1;}

    void build(int p, int L, int R){
        if (L == R)
            sum[p] = maxSum[p] = leftSum[p] = rightSum[p] = A[L];
        else{
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            sum[p] = sum[left(p)] + sum[right(p)];
            leftSum[p] = max(leftSum[left(p)], sum[left(p)] + leftSum[right(p)]);
            rightSum[p] = max(rightSum[right(p)], sum[right(p)] + rightSum[left(p)]);
            maxSum[p] = max(max(maxSum[left(p)], maxSum[right(p)]), rightSum[left(p)] + leftSum[right(p)]);
        }
    }

    ret_t rmq(int p, int L, int R, int i, int j){
        if (i > R || j < L) return {-1, -1, -1, -1, 0};
        if (L >= i && R <= j) return {leftSum[p], rightSum[p], sum[p], maxSum[p], 1};

        ret_t p1 = rmq(left(p), L, (L + R) / 2, i, j);
        ret_t p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);
        if (!p1.valid) return p2;
        if (!p2.valid) return p1;

        ret_t ret;
        ret.sum = p1.sum + p2.sum;
        ret.left = max(p1.left, p1.sum + p2.left);
        ret.right = max(p2.right, p2.sum + p1.right);
        ret.maxSum = max(max(p1.maxSum, p2.maxSum), p1.right + p2.left);
        ret.valid = 1;
        return ret;
    }

public:
    SegmentTree(const vector<int>& _A){
        A = _A;
        n = (int)A.size();
        sum.assign(4 * n, 0);
        maxSum.assign(4 * n, 0);
        leftSum.assign(4 * n, 0);
        rightSum.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j){
        return rmq(1, 0, n - 1, i, j).maxSum;
    }

    void debugPrint(){
        cout << n << "\n";
        for (int it: maxSum)
            cout << it << " ";
        cout << "\n";
    }
};

int main(){
    int N;
    scanf("%d", &N);
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    SegmentTree st(A);

    int M;
    scanf("%d", &M);
    while (M--){
        int i, j;
        scanf("%d %d", &i, &j);
        if (i < 1) i = 1;
        if (j > N) j = N;
        printf("%d\n", st.rmq(i - 1, j - 1));
    }
    return 0;
}
