#include<bits/stdc++.h>
 
using namespace std;

struct SegmentTree {
    const int n;
    vector<long long> vec;
    SegmentTree(int n) : n(n), vec(4 << __lg(n)) {}
    SegmentTree(vector<int> init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                vec[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        vec[p] = vec[2 * p] + vec[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const int val) {
        if (r - l == 1) {
            vec[p] = val;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, val);
        } else {
            modify(2 * p + 1, m, r, x, val);
        }
        pull(p);
    }
    void modify(int p, const int val) {
        modify(1, 0, n, p, val);
    }
    long long rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return 0;
        }
        if (l >= x && r <= y) {
            return vec[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    long long rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree seg(a);

    for (int i = 0; i < q; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int k, x;
            cin >> k >> x;
            seg.modify(k-1, x);
        } else {
            int l, r; qu
            cin >> l >> r;
            // query is 0-index in form [l, r[
            cout << seg.rangeQuery(l-1, r) << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}
