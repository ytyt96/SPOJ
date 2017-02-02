#include <bits/stdc++.h>

using namespace std;

vector<int> A;

struct segment_tree {
    struct node_t {
        int sum, left_sum, right_sum, max_sum;
    };

    vector<node_t> st;
    int n;

    inline int left(int p) {
        return p << 1;    
    }

    inline int right(int p) {
        return (p << 1) + 1;
    }


    node_t merge(const node_t &l, const node_t &r) {
        return node_t({ l.sum + r.sum,
                        max(l.left_sum, l.sum + r.left_sum),
                        max(r.right_sum, r.sum + l.right_sum),
                        max(max(l.max_sum, r.max_sum), l.right_sum + r.left_sum)
                      });
    }

    void build(int p, int L, int R) {
        if (L == R) 
            st[p].sum = st[p].max_sum = st[p].left_sum = st[p].right_sum = A[L];
        else {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p] = merge(st[left(p)], st[right(p)]);
        }
    }

    node_t query(int p, int L, int R, int i, int j) {
        if (L > j || R < i)
            return node_t({INT_MIN, INT_MIN, INT_MIN, INT_MIN});
        if (L >= i && R <= j)
            return st[p];
        node_t p1 = query(left(p), L, (L + R) / 2, i, j);
        node_t p2 = query(right(p), (L + R) / 2 + 1, R, i, j);
        if (p1.sum == INT_MIN)
            return p2;
        if (p2.sum == INT_MIN)
            return p1;

        return merge(p1, p2);
    }

    node_t update(int p, int L, int R, int target, int val) {
        if (L > target || R < target)
            return st[p];
        if (L == R) 
            return st[p] = {val, val, val, val};
        
        return st[p] = merge(update(left(p), L, (L + R) / 2, target, val),
                             update(right(p), (L + R) / 2 + 1, R, target, val));
    }

    segment_tree() {
        n = A.size();
        st.assign(n * 4, node_t());
        build(1, 0, n - 1);
    }

    int query(int i, int j) {
        return query(1, 0, n - 1, i, j).max_sum;
    }

    void update(int target, int val) {
        update(1, 0, n - 1, target, val); 
    }
};

int main() {
    int N;
    scanf("%d", &N);
    A.assign(N, 0);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    segment_tree st;

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 0)
            st.update(x - 1, y);
        else if (op == 1)
            printf("%d\n", st.query(x - 1, y - 1));
    }
    return 0;
}
