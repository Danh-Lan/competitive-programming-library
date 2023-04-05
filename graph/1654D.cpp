// thank 1390632669

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int N = 2e5;

struct edge {
    int dest, x, y;
};

map<int,int> mp[N+1];
long long n, t, ans;
// cnt[i] : exp of p of vertex i, val[i] : max(cnt[i]) --> for lcm
long long val[N+1], cnt[N+1];
vector<edge> tree[N+1];

void factor() {
    for (int i = 2; i <= N; ++i) {
        int num = i;
        for (int j = 2; j <= sqrt(i)+1; ++j) {
            while (num % j == 0) {
                num /= j;
                mp[i][j]++;
            }
        }

        if (num > 1) mp[i][num]++;
    }
}

long long qpow(long long a, int pow) {
    long long ans = 1LL;
    while (pow) {
        if (pow % 2 == 1) ans = (ans%MOD * a) % MOD;

        a = (a%MOD * a%MOD) % MOD;
        pow /= 2;
    }

    return ans;
}

void dfs_traverse(int u, int fa) { // only to find lcm
    for (auto v : tree[u]) {
        if (v.dest == fa) continue;
        for (auto i : mp[v.y]) cnt[i.first] -= i.second;
        for (auto i : mp[v.x]) {
            cnt[i.first] += i.second;
            val[i.first] = max(val[i.first], cnt[i.first]);
        }
        dfs_traverse(v.dest, u);
        for (auto i : mp[v.x]) cnt[i.first] -= i.second;
        for (auto i : mp[v.y]) cnt[i.first] += i.second;
    }
}
void dfs_ans(int u, int fa, int t) {
    ans = (ans + t) % MOD;
    for (auto v : tree[u]) {
        if (v.dest == fa) continue;
        dfs_ans(v.dest, u, (long long)t * v.y % MOD * qpow(v.x, MOD - 2) % MOD);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    factor();

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; ++test) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            tree[i].clear();
            val[i] = 0; cnt[i] = 0;
        }
        t = 1LL; ans = 0LL;

        for (int i = 0; i < n-1; ++i) {
            int a, b, x, y;
            cin >> a >> b >> x >> y;

            int gcd = __gcd(x, y);
            x /= gcd; y /= gcd;

            tree[a].push_back({b, x, y});
            tree[b].push_back({a, y, x});
        }

        dfs_traverse(1, 0);
        for (int i = 1; i <= n; ++i) {
            t = (t * qpow(i, val[i])) % MOD;
        }
        dfs_ans(1, 0, t);
        cout << ans << '\n';
    }

    return 0;
}