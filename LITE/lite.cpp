#include <bits/stdc++.h>

using namespace std;

struct segment_tree {
    vector<int> st;
    vector<bool> lazy;

    size_t n;

    inline int left(int p) {
        return p << 1;
    }

    inline int right(int p) {
        return (p << 1) + 1;
    }

    void propagate(int p, int L, int R) {
        if (lazy[p]) {
            if (L != R) {
                lazy[left(p)] = !lazy[left(p)];
                lazy[right(p)] = !lazy[right(p)];
            }
            st[p] = (R - L + 1) - st[p];
            lazy[p] = false;
        }
    }

    int* update(int p, int L, int R, int i, int j) {
        propagate(p, L, R);

        if (L > j || R < i)
            return st[p];
        if (L >= i && R <= j) {
            lazy[p] = true;
            propagate(p, L, R);
            return st[p];
        }

        int *p1 = update(left(p), L, (L + R) / 2, i, j);
        int *p2 = update(right(p), (L + R) / 2 + 1, R, i, j);
        st[0][p] = p1[0] + p2[0];
    }

    int query(int p, int L, int R, int i, int j) {
        if (L > j || R < i)
            return 0;
        propagate(p, L, R);
        if (L >= i && R <= j)
            return st[p];
        return query(left(p), L, (L + R) / 2, i, j) + 
               query(right(p), (L + R) / 2 + 1, R, i, j);
    }

    segment_tree(int N): n(N) {
        st.assign(n * 4, 0);
        lazy.assign(n * 4, false);
    }

    void update(int i, int j) {
        update(1, 0, n - 1, i, j);
    }

    int query(int i, int j) {
        return query(1, 0, n - 1, i, j);
    }
};

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    segment_tree st(N);
    while (M--) {
        int op, S, E;
        scanf("%d %d %d", &op, &S, &E);
        S--, E--;
        if (op == 0)
            st.update(S, E);
        else
            printf("%d\n", st.query(S, E));
    }
    return 0;
}
