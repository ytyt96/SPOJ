#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y, z; 
};

struct segment_tree {
    vector<point> st;
    vector<int> lazy;
    size_t n;

    inline int left(int p) {
        return p << 1;
    }

    inline int right(int p) {
        return (p << 1) + 1;
    }

    void build(int p, int L, int R) {
        if (L == R)
            st[p].x = 1;
        else {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p].x = st[left(p)].x + st[right(p)].x;
        }
    }

    void propagate(int p, int L, int R) {
        if (lazy[p]) {
            lazy[p] %= 3;
            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            if (lazy[p] == 1) {
                int temp = st[p].z;
                st[p].z = st[p].y;
                st[p].y = st[p].x;
                st[p].x = temp;
            }
            else if (lazy[p] == 2) {
                int temp = st[p].z;
                st[p].z = st[p].x;
                st[p].x = st[p].y;
                st[p].y = temp;
            }
            lazy[p] = 0;
        }
    }

    point update(int p, int L, int R, int i, int j) {
        propagate(p, L, R);

        if (L > j || R < i) 
            return st[p];

        if (L >= i && R <= j) {
            lazy[p] = 1;
            propagate(p, L, R);
            return st[p];
        }

    
        point p1 = update(left(p), L, (L + R) / 2, i, j);
        point p2 = update(right(p), (L + R) / 2 + 1, R, i, j);
        st[p].x = p1.x + p2.x;
        st[p].y = p1.y + p2.y;
        st[p].z = p1.z + p2.z;
        return st[p];
    }

    int query(int p, int L, int R, int i, int j) {
        propagate(p, L, R);

        if (L > j || R < i)
            return 0;

        if (L >= i && R <= j)
            return st[p].x;

        return query(left(p), L, (L + R) / 2, i, j) + 
               query(right(p), (L + R) / 2 + 1, R, i, j);
    }

    segment_tree(int N): n(N) {
        st.assign(4 * n, point());
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int update(int i, int j) {
        update(1, 0, n - 1, i, j);
    }

    int query(int i, int j) {
        return query(1, 0, n - 1, i, j);
    }
};


int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    segment_tree st(N);
    while (Q--) {
        int op, A, B;
        scanf("%d %d %d", &op, &A, &B);
        if (op == 0)
            st.update(A, B);
        else
            printf("%d\n", st.query(A, B));
    }
    return 0;
}
