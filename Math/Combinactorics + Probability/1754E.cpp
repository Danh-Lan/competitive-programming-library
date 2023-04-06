#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

long long pow(long long base, int power) {
    long long ans = 1LL;
    while (power) {
        if (power % 2 == 1) {
            ans = (ans * base) % MOD;
        }
        
        base = (base * base) % MOD;
        power /= 2;
    }

    return ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; ++test) {
        int n; cin >> n;
        int a[n];
        int cnt_zero = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] == 0) {
                cnt_zero++;
            }
        }

        int miss = 0;
        for (int i = 0; i < cnt_zero; ++i) {
            if (a[i] == 1) miss++;
        }

        long long ans = 0LL;
        for (int i = miss; i >= 1; --i) {
            ans = (ans + pow(1LL*i*i, MOD-2)) % MOD; 
        }

        long long x = (1LL*n*(n-1)/2)%MOD;
        ans = ((ans%MOD) * x) % MOD;
        cout << ans << '\n';
    }

    return 0;
}