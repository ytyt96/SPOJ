#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> A;

struct segment_tree {
    vector<pair<int, int>> st;
    vector<int> lazy;
    size_t n;
    int retval;

    inline int left(int p) {
        return p << 1;
    }

    inline int right(int p) {
        return (p << 1) + 1;
    }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = {A[L].first, L};
        else {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p] = st[left(p)];
        }
    }

    void propagate(int p, int L, int R) {
        if (lazy[p]) {
            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }
            st[p].first += lazy[p];
            lazy[p] = 0;
        }
    }

    void update(int p, int L, int R, int i, int j, int val) {
        propagate(p, L, R);

        if (L > j || R < i)
            return;
        if (L >= i && R <= j) {
            lazy[p] = val;
            propagate(p, L, R);
            return;
        }

        update(left(p), L, (L + R) / 2, i, j, val);    
        update(right(p), (L + R) / 2 + 1, R, i, j, val);
        st[p] = st[left(p)];
    }

    void query(int p, int L, int R, int val) {
        propagate(p, L, R);

        if (L != R) {
            propagate(left(p), L, (L + R) / 2);
            propagate(right(p), (L + R) / 2 + 1, R);
        }

        if (L == R) {
            if (st[p].first >= val) 
                retval = L;
            return;
        }

        if (st[right(p)].first >= val)
            retval = st[right(p)].second;

        if (st[right(p)].first < val)
            query(right(p), (L + R) / 2 + 1, R, val);
        else
            query(left(p), L, (L + R) / 2, val);
    }

    pair<int, int> find_nth(int p, int L, int R, int index) {
        propagate(p, L, R);

        if (L == R)
            return {st[p].first, L};
        if (index <= (L + R) / 2)
            return find_nth(left(p), L, (L + R) / 2, index);
        else
            return find_nth(right(p), (L + R) / 2 + 1, R, index);
    }

    segment_tree() {
        n = A.size();
        st.assign(4 * n, pair<int, int>());
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    void update(int i, int j, int val) {
        update(1, 0, n - 1, i, j, val);
    }

    int query(int val) {
        retval = -1;
        query(1, 0, n - 1, val);
        if (retval == -1) 
            return n;
        return retval;
    }

    pair<int, int> find_nth(int index) {
        return find_nth(1, 0, n - 1, index);
    }
};

int main(){
    int N, Q;
    scanf("%d %d", &N, &Q);
    A.assign(N, pair<int, int>());
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }

    sort(A.begin(), A.end());

    vector<int> finder(N);
    for (int i = 0; i < N; i++)
        finder[A[i].second] = i;

    segment_tree st;

    for (int i = 0; i < Q; i++) {
        int op, val;
        scanf("%d %d", &op, &val);
        if (op == 1) {
            pair<int, int> ret = st.find_nth(finder[val - 1]);
            int p = st.query(ret.first + 1);

            swap(finder[val - 1], finder[A[p - 1].second]);
            swap(A[p - 1].second, A[ret.second].second);
            st.update(p - 1, p - 1, 1);
        }
        else if (op == 2) {
            printf("%d\n", N - st.query(val));
        }
        else 
            st.update(st.query(val), N - 1, -1);
    }

    return 0;
}
