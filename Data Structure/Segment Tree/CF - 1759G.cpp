// https://codeforces.com/contest/1759/submission/181469821
// thank you jiangly
// explanation at the end

#include<bits/stdc++.h>
 
using namespace std;

template<class Info,
    class Merge = plus<Info>> // plus<X> --> operator +
    // only for readability, instead of merge(info1, info2),
    // info1 + info2 works 
struct SegmentTree {
    const int n;
    const Merge merge;
    vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                // pos is 1-indexed, so in ]l;r] = ]l;l+1],
                // l correspond to empty, r=l+1 to taking the only element
                info[p].pos = info[p].sum < 0 ? r : l;
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
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            info[p].pos = info[p].sum < 0 ? r : l;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};
 
struct Info {
    int sum;
    int pre;
    int pos;
    Info(int x = 0) : sum(x), pre(min(0, x)) {}
};
 
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.pre = min(a.pre, a.sum + b.pre);
    c.pos = c.pre == a.sum + b.pre ? b.pos : a.pos;
    return c;
}

void solve() {
    int n;
    cin >> n;
    
    vector<int> b(n / 2);
    for (int i = 0; i < n / 2; i++) {
        cin >> b[i];
    }
    
    if (set<int>(b.begin(), b.end()).size() != b.size()) {
        cout << -1 << "\n";
        return;
    }
    
    vector<int> a(n, 1);
    for (auto x : b) {
        a[x - 1] = -1;
    }
    SegmentTree<Info> seg(vector<Info>(a.begin(), a.end()));
    
    if (seg.rangeQuery(0, n).pre < 0) {
        cout << -1 << "\n";
        return;
    }
    
    for (int i = 0; i < n / 2; i++) {
        int x = seg.rangeQuery(0, b[i] - 1).pos;
        seg.modify(x, 0);
        seg.modify(b[i] - 1, 0);
        cout << x + 1 << " " << b[i] << " \n"[i == n / 2 - 1];
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
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}

/*
Imagine there's a bracket sequence s of length n, for each i, we set s_bi
to a right bracket and set the rest to left brackets 
(e.g. the first example input 4 3 6 is (())()). 
So our target would became for each right bracket we want to match it to a left bracket to its left, 
so the solution exists only if it's a valid bracket sequence, i.e. all prefix sums are greater than or equal to 0.

Because we want the lexicographically minimal permutation, so for each bi we want to find the smallest j<bi
such that if we remove sj and sbi, the remaining bracket sequence is still valid. 
We claim that we should choose the largest j such that prefj−1=0. 
In order to find such j, we use a segment tree by maintaining the sum, min prefix, and the position of the min prefix.
https://codeforces.com/blog/entry/109254
*/
