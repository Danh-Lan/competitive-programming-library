// source : SSRS
// can't use INT_MAX because the loop doesn't deal with case that doesn't exist
// so INT_MAX can overflow

#include <bits/stdc++.h>
 
using namespace std;

const int INF = 1e9 + 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int test = 1;
    //cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        int n, l, k; cin>>n>>l>>k;
        int coor[n+1], sp[n];
        for (int i = 0; i < n; ++i)
        {
            cin>>coor[i];
        }
        coor[n] = l;
        for (int i = 0; i < n; ++i)
        {
            cin>>sp[i];
        }

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;

        for (int i = 0; i <= k; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                for (int l = j+1; l <= n ; ++l)
                {
                    int i2 = i + (l - j - 1);
                    if (i2 <= k) {
                        dp[i2][l] = min(dp[i2][l], dp[i][j] + sp[j]*(coor[l]-coor[j]));
                    }
                }
            }
        }
        
        int ans = INF;
        for (int i = 0; i <= k; ++i)
        {
            ans = min(ans, dp[i][n]);
        }
        cout<<ans<<endl;
    }

    return 0;
}