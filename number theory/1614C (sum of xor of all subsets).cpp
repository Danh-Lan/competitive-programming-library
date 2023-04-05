#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n, m; cin>>n>>m;
        long long ans = 0LL;
        for (int i = 0; i < m; ++i) {
            int l, r;
            long long x; 
            cin>>l>>r>>x;
            ans |= x;
        }

        ans%=MOD;

        for (int i = 0; i < n-1; ++i) {
            ans = (ans*2)%MOD;
        }

        cout<<ans<<endl;
    }

    return 0;
}