#include <bits/stdc++.h>

using namespace std;

struct point {
    int left, right, block, id;
};

bool cmp(const point &lhs, const point &rhs) {
    if (lhs.block < rhs.block)
        return true;
    else if (lhs.block > rhs.block)
        return false;
    else
        return lhs.right < rhs.right;
}

int main(){
    int n, q;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int block_size = sqrt(n);

    scanf("%d", &q);
    vector<point> query(q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &query[i].left, &query[i].right);
        query[i].left--, query[i].right--;
        query[i].block = query[i].left / block_size;
        query[i].id = i;
    }

    sort(query.begin(), query.end(), cmp);

    vector<int> solution(q);
    vector<int> hash(1000100);

    int left = 0, right = 0, answer = 1;
    hash[A[0]] = 1;

    for (const point &task : query) {
        while (left < task.left) {
            hash[A[left]]--;
            answer -= (hash[A[left]] == 0);
            left++;
        }
        while (left > task.left) {
            left--;
            hash[A[left]]++;
            answer += (hash[A[left]] == 1);
        }
        while (right < task.right) {
            right++;
            hash[A[right]]++;
            answer += (hash[A[right]] == 1);
        }
        while (right > task.right) {
            hash[A[right]]--;
            answer -= (hash[A[right]] == 0);
            right--;
        }
        solution[task.id] = answer;
    }

    for (int answer : solution)
        printf("%d\n", answer);

    return 0;
}
