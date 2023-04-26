#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e6;
vector<long long> fact(N+1, 0LL);

void calFactorial(int mod) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= N; ++i) {
        fact[i] = (i*fact[i-1]) % mod;
    }
}

long long modPow(long long a, long long x, int mod) {
    long long res = 1;
    while (x > 0) {
        if (x % 2 != 0) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        x /= 2;
    }
    return res;
}

long long modInverse(long long a, int mod) {
    return modPow(a, mod-2, mod);
}
long long modBinomial(long long n, long long k, int mod) {
    long long numerator = (fact[n] * modInverse(fact[n-k], mod)) % mod;
    long long denominator = fact[k];

    return ( numerator* modInverse(denominator,mod) ) % mod;
}

void solve() {
    calFactorial(MOD);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        cout << modBinomial(a, b, MOD) << '\n';
    }
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

// CSES - Binomial Coefficients