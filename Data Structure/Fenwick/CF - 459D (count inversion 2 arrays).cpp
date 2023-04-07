#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
    int n; vector<int> t;
    Fenwick() {}
    Fenwick(int _n) {
        n = _n; t.assign(n + 1, 0);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) ans += t[i];
        return ans;
    }
    void upd(int i, int val) {
        if (i <= 0) return;
        for (; i <= n; i += (i & -i)) t[i] += val;
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<int> f(n), g(n);
        map<int,int> mf, mg;
        for (int i = 0; i < n; ++i) {
            mf[a[i]]++;
            f[i] = mf[a[i]];
        }
        for (int i = n-1; i >= 0; --i) {
            mg[a[i]]++;
            g[i] = mg[a[i]];
        }
        
        Fenwick fen(1e6+1);
        long long ans = 0LL;
        for (int i = n-1; i >= 0; --i) {
            ans += fen.query(f[i]-1);
            fen.upd(g[i], 1);
        }

        cout << ans << '\n';
    }

    return 0;
}