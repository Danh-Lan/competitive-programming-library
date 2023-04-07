#include <bits/stdc++.h>

using namespace std;

const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int N;
        cin>>N;
        
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin>>a[i];
        
        long long ans = 0;
        
        for (int i = 1; i <= N; i++) {
            long long dp[N+1][i+1][i] = {0};
            for (int j = 0; j <= N; j++) {
                for (int k = 0; k <= i; k++) {
                    for(int l = 0; l < i; l++) {
                        dp[j][k][l] = 0LL;
                    }
                }
            }
            dp[0][0][0] = 1;
            for (int j = 0; j < N; j++) {
                for (int k = 0; k <= i; k++) {
                    for(int l = 0; l < i; l++) {
                        dp[j+1][k][l] = (dp[j+1][k][l]+dp[j][k][l])%MOD;
                        if (k != i) dp[j+1][k+1][(l+a[j])%i] = (dp[j+1][k+1][(l+a[j])%i]+dp[j][k][l])%MOD;
                    }
                }
            }
            ans = (ans + dp[N][i][0]) % MOD;
        }
        
        cout<<ans<<"\n";
    }

    return 0;
}