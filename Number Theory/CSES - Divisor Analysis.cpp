#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 1e9 + 7;

long long modPow(long long a, long long pow, int mod) {
    if (a <= 0) return 0;

    long long ans = 1LL;
    while (pow > 0) {
        if (pow % 2 == 1) {
            ans = (ans * a) % mod;
        }

        a = (a * a) % mod;
        pow /= 2;
    }

    return ans;
}

long long modInverse(long long a, int mod) {
    return modPow(a, mod-2, mod);
}

// number of divisor = PI(pow[i]+1) = phi
// sum of divsor = PI(p[i]^(pow[i]+1)-1/(p[i]-1))
// product of divisor = PI(p[i]^(phi*pow[i]/2))
void solve() {
    int n;
    cin >> n;
    int p[n], pow[n];
    long long cnt = 1, sum = 1, prod = 1;
    long long powProd = 1;
    
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> pow[i];
        cnt = (cnt * (pow[i]+1)) % MOD;
        powProd = (powProd * (pow[i]+1)) % (MOD-1);
        sum = (sum * (modPow(p[i], 1LL*pow[i]+1, MOD) + MOD-1) % MOD * modInverse(p[i]-1, MOD)) % MOD;
    }

    // since (2, MOD-1) = 2, we can't take mod before divide by 2
    long long powProdDiv2 = 1;
    int div2 = -1;
    // div2 != -1 --> there is some pow[i]+1 divisibile by 2
    for (int i = 0; i < n; ++i) {
        if (pow[i] % 2 == 1) {
            powProdDiv2 = (pow[i]+1)/2;
            div2 = i;
            break;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i != div2) {
            powProdDiv2 = (powProdDiv2 * (pow[i]+1)) % (MOD-1);
        }
    }

    for (int i = 0; i < n; ++i) {
        long long pw = 1;
        if (pow[i] % 2 == 0) {
            pw = (powProd * pow[i]/2) % (MOD-1);
        } else {
            // div2 is guarantee to != -1
            pw = (powProdDiv2 * pow[i]) % (MOD-1);
        }

        prod = (prod * modPow(p[i], pw, MOD)) % MOD;
    }

    cout << cnt << ' ' << sum << ' ' << prod << '\n';
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
