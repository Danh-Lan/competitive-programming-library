// https://codeforces.com/contest/1804/submission/197089405
// in jiangly's solution, q.push(y) is not important because 
// the neighbor of cycle already cover all the vertex

#include<bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, m;
        cin >> n >> m;
        
        vector<int> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u] |= 1 << v;
            adj[v] |= 1 << u;
        }
        
        // dp[s] : subset s, lowest bit = u
        // bit i > u = 1 --> there is a chain from u to i
        vector<int> dp(1 << n);
        for (int i = 0; i < n; i++) {
            dp[1 << i] |= 1 << i;
        }
        for (int s = 1; s < (1 << n); s++) {
            int sadj = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    sadj |= adj[i];
                }
            }
            int lo = __builtin_ctz(s);
            if (sadj == (1 << n) - 1 && (adj[lo] & dp[s])) {
                // adj[lo] & dp[s] --> exist a cycle
                int nxt = lo;
                vector<int> cyc;
                int S = s;
                while (S != (1 << lo)) {
                    int t = __builtin_ctz(dp[S] & adj[nxt]);
                    cyc.push_back(t);
                    S ^= 1 << t;
                    nxt = t;
                }
                cyc.push_back(lo);
                cout << "Yes\n";
                vector<int> a(n, -1);
                queue<int> q;
                for (int i = 0; i < cyc.size(); i++) {
                    a[cyc[i]] = cyc[(i + 1) % cyc.size()];
                    q.push(cyc[i]);
                }
                while (!q.empty()) {
                    int x = q.front();
                    q.pop();
                    for (int y = 0; y < n; y++) {
                        if (~adj[x] >> y & 1) {
                            continue;
                        }
                        if (a[y] == -1) {
                            a[y] = x;
                        }
                    }
                }
                for (int i = 0; i < n; i++) {
                    cout << a[i] + 1 << ' ';
                } cout << '\n';
                return 0;
            }

            int mask = 0; // possible neighbors of subset s
            for (int i = 0; i < n; i++) {
                if (dp[s] >> i & 1) {
                    mask |= adj[i];
                }
            }
            for (int i = lo; i < n; i++) {
                if ((~s & mask) >> i & 1) {
                    dp[s | 1 << i] |= 1 << i;
                }
            }
        }
        
        cout << "No\n";
    }

    return 0;
}