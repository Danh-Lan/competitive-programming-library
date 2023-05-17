// https://codeforces.com/blog/entry/115296?#comment-1024618
// this comment is the easiest to understand

#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 998244353;
const int N = 300000;
long long fact[N+1];

long long add(long long a, long long b, int mod) {
    long long ans = a % mod + b % mod;
    ans %= mod;
    if (ans < 0) ans += mod;

    return ans;
}

long long mul(long long a, long long b, int mod) {
    long long ans = (a % mod) * (b % mod);
    ans %= mod;
    if (ans < 0) ans += mod;
    return ans;
}

void calFact(int mod) {
    fact[0] = fact[1] = 1LL;
    for (int i = 2; i <= N; ++i) {
        fact[i] = mul(i, fact[i-1], mod);
    }
}

long long qpow(long long a, long long p, int mod) {
    if (p < 0) return 0LL;
    if (a == 0) return 0LL;
    if (a == 1) return 1LL;
    if (a == -1) {
        if (p % 2 == 0) return 1LL;
        else return -1LL;
    }

    long long ans = 1LL;
    while (p > 0) {
        if (p % 2 == 1) {
            ans = mul(ans, a, mod);
        }

        a = mul(a, a, mod);
        p /= 2;
    }

    return ans; 
}

long long qbinom(long long n, long long k, int mod) {
    assert(fact[0] == 1LL);

    if (k < 0 || k > n) return 0LL;

    if (k > n-k) k = n-k;

    long long numerator = mul(fact[n], qpow(fact[n-k], mod-2, mod), mod);
    long long denominator = qpow(fact[k], mod-2, mod);

    return mul(numerator, denominator, mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    calFact(MOD);

    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        long long n, m, k;
        cin >> n >> m >> k;

        if (m*(k+1) > n) {
            cout << 0 << '\n';
        } else {
            long long ans = 0LL;
            for (long long i = 0; i <= m; ++i) {
                long long res = mul(qbinom(n-(k+1)*m-k*i+m, m, MOD), qbinom(m, i, MOD), MOD);
                res = mul(res, qpow(2, m-i, MOD), MOD);
                res = mul(res, qpow(-1, i, MOD), MOD);
                
                ans = add(ans, res, MOD);
            }

            cout << ans << '\n';
        }
    }

    return 0;
}