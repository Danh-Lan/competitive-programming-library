// thanks jiangly as usual
// this implementation is quite memory efficient
// if we use LCA, don't call array[N+1][LG+1], it will get MLE

#include<bits/stdc++.h>
 
using namespace std;

const int N = 5e6;
vector<int> phi(N+1, -1);

void totientSieve() {
    for (int i = 0; i <= N; ++i) {
        phi[i] = i;
    }

    for (int i = 2; i <= N; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}

template<class Info,
    class Merge = plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
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
    void change(int p, int l, int r, int x, int v) {
        if (info[p].a.back()[0] == v) {
            info[p].a.pop_back();
        }

        // this replace pull(p)
        for (auto &it : info[p].a) {
             it[1] -= 1;
        }
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            change(2 * p, l, m, x, v);
        } else {
            change(2 * p + 1, m, r, x, v);
        }
    }
    void change(int p, int v) {
        change(1, 0, n, p, v);
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
    bool empty;
    vector<array<int, 2>> a;
    
    Info() : empty{true} {}
    Info(int x) {
        empty = false;
        int t = 0;
        while (true) {
            a.push_back({x, t});
            if (x == 1) {
                break;
            }
            x = phi[x];
            t++;
        }
        reverse(a.begin(), a.end());
    }
};
 
Info operator+(Info a, Info b) {
    if (a.empty) {
        return b;
    }
    if (b.empty) {
        return a;
    }
    Info c;
    c.empty = false;
    int i = 0, j = 0;
    while (i < a.a.size() && j < b.a.size()) {
        if (a.a[i][0] < b.a[j][0]) {
            i++;
        } else if (a.a[i][0] > b.a[j][0]) {
            j++;
        } else {
            c.a.push_back({a.a[i][0], a.a[i][1] + b.a[j][1]});
            i++, j++;
        }
    }
    return c;
}

struct DSU {
    vector<int> f;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
    }
    
    int par(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return par(x) == par(y);
    }
    
    bool merge(int x, int y) {
        x = par(x);
        y = par(y);
        if (x == y) {
            return false;
        }
        if (x < y) swap(x, y);
        f[y] = x;
        return true;
    }
};

void solve() {
    totientSieve();

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    SegmentTree<Info> seg(vector<Info>(a.begin(), a.end()));
    
    DSU dsu(n + 1);
    
    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        
        l--;
        if (op == 1) {
            // the loop suppose in DSU that par(x) >= x
            // I add in merge() if (x < y) for clarity
            for (int i = dsu.par(l); i < r; i = dsu.par(i + 1)) {
                if (a[i] == 1) {
                    dsu.merge(i + 1, i);
                } else {
                    seg.change(i, a[i]);
                    a[i] = phi[a[i]];
                }
            }
        } else {
            auto info = seg.rangeQuery(l, r);
            cout << info.a.back()[1] << "\n";
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
