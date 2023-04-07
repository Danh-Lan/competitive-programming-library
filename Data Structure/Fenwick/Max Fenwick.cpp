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
        int n; cin >> n;
        vector<vector<int>> a(n);
        map<int, int> normalize; // to normalize

        // add +1 to all to use 1-index fenwick
        for (int i = 0; i < n; ++i) {
            int k; cin >> k;
            vector<int> album = {1};
            for (int j = 0; j < k; ++j) {
                int cool; cin >> cool;
                ++cool;
                if (album.size() == 1) album.push_back(cool);
                else if (album.back() < cool) album.push_back(cool);
            }

            for (int j = 0; j < album.size(); ++j) {
                normalize[album[j]] = 1;
            }

            a[i] = album;
        }

        int cur = 1;
        for (auto it : normalize) {
            normalize[it.first] = cur;
            cur++;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < a[i].size(); ++j) {
                a[i][j] = normalize[a[i][j]];
            }
        }

        sort(a.begin(), a.end(), [&] (auto& a1, auto& a2) {
            return (a1.back() < a2.back());
        });

        int mx = normalize.size();
        MaxFenwick maxFen(mx);
        vector<int> dp(mx+1, 0);
        // dp[i] = max(dp[i], max(dp[k] + (a[i].size-j))), k \in [a[i][j-1], a[i][j]-1];
        // because a[i].size-j is decreasing, k can be from 0 to a[i][j]-1
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < a[i].size(); ++j) {
                dp[a[i].back()] = max(dp[a[i].back()], ((int)a[i].size()-j) + maxFen.query(a[i][j]-1));                
            }

            maxFen.update(a[i].back(), dp[a[i].back()]);
        }

        cout << dp[mx] << '\n';
    }

    return 0;
}

// 1801C