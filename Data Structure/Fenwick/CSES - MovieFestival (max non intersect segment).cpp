#include<bits/stdc++.h>
 
using namespace std;

// only max query of type [0; k]
struct MaxFenwick {
    int N;
    vector<int> Fen;
    MaxFenwick(int n): N(n), Fen(n+1, -1) { }

    void update (int i, int val) {
        while (i <= N) {
            Fen[i] = max(Fen[i], val);
            i += i & -i;
        }
    }

    int query (int i) {
        int ans = 0;
        while (i > 0) {
            ans = max(ans, Fen[i]);
            i -= i & -i;
        }
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    pair<int, int> p[n];
    map<int, int> m;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
        m[p[i].first] = m[p[i].second] = 1;
    }

    int cnt = 1;
    for (auto it : m) {
        m[it.first] = cnt;
        cnt++;
    }

    sort(p, p+n);
    for (int i = 0; i < n; ++i) {
        p[i].first = m[p[i].first];
        p[i].second = m[p[i].second];
    }

    MaxFenwick maxFen(m.size()+1);

    for (int i = 0; i < n; ++i) {
        int mxL = 1 + maxFen.query(p[i].first); // see this movie
        int mxR = maxFen.query(p[i].second); // doesn't see this movie
        maxFen.update(p[i].second, max(mxL, mxR));
    }

    cout << maxFen.query(m.size()+1) << endl;
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
