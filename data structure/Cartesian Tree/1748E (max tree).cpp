#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 1e9 + 7;

// same value --> left-most index
vector<int> cartesian_tree_max(vector<int> &A) {
    int N = A.size();
    vector<int> pr(N, -1);
    stack<int> st;
    st.push(0);
    for (int i = 1; i < N; i++) {
        int prev = -1;
        while (!st.empty()) {
            int j = st.top();
            if (A[i] > A[j]) {
                st.pop();
                if (prev != -1) {
                    pr[prev] = j;
                }
                prev = j;
            } else {
                break;
            }
        }

        if (prev != -1) {
            pr[prev] = i;
        }
        st.push(i);
    }

    while (st.size() >= 2) {
        int x = st.top();
        st.pop();
        pr[x] = st.top();
    }

    return pr;
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
        int n, m ; cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // convert a[i] to relative decreasing order 
        // if a[i] with same value, prioritize left-most
        vector<pair<int, int>> P(n);
        for (int i = 0; i < n; ++i) {
            P[i] = {a[i], -i};
        }
        sort(P.begin(), P.end());
        for (int i = 0; i < n; ++i) {
            a[i] = lower_bound(P.begin(), P.end(), make_pair(a[i], -i)) - P.begin();
        }

        vector<int> p = cartesian_tree_max(a);

        int root;
        for (int i = 0; i < n; ++i) {
            if (p[i] == -1) {
                root = i;
                break;
            }
        }
        
        vector<vector<int>> c(n);
        for (int i = 0; i < n; ++i) {
            if (i != root) {
                c[p[i]].push_back(i);
            }
        }
        
        vector<int> bfs;
        queue<int> Q;
        Q.push(root);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            bfs.push_back(v);
            for (int w : c[v]) {
                Q.push(w);
            }
        }
        reverse(bfs.begin(), bfs.end());
        vector<vector<long long>> dp(n, vector<long long>(m, 1));
        for (int v : bfs) {
            for (int w : c[v]) {
                for (int i = 1; i < m; ++i) {
                    dp[w][i] += dp[w][i-1];
                    dp[w][i] %= MOD;
                }
                if (w < v) {
                    dp[v][0] = 0;
                    for (int i = 0; i < m - 1; ++i) {
                        dp[v][i+1] *= dp[w][i];
                        dp[v][i+1] %= MOD;
                    }
                } else {
                    for (int i = 0; i < m; ++i) {
                        dp[v][i] *= dp[w][i];
                        dp[v][i] %= MOD;
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            ans += dp[root][i];
        }
        ans %= MOD;
        cout << ans << '\n';
    }
 
    return 0;
}