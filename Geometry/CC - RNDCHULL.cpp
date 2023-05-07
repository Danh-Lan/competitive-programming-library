// copy from https://www.codechef.com/viewsolution/54703393

#include <bits/stdc++.h>
using namespace std;

const int N = 33;
const int MOD = 998244353;

int n;
int x[N], y[N];

int cross(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
  return (q.first - p.first) * (r.second - q.second) - (q.second - p.second) * (r.first - q.first);
}

int solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &y[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;

      for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
          if (ii == jj) continue;

          pair<int, int> p = {x[i], y[ii]};
          pair<int, int> q = {x[j], y[jj]};

          int incr = 0, kk;
          if (cross({0, 0}, p, q) > cross({0, 1}, p, q)) {
            incr = 1;
            kk = 0;
          } else {
            incr = -1;
            kk = n - 1;
          }

          int way = 1;
          if (cross({0, 0}, p, q) > cross({1, 0}, p, q)) {
            int cnt = 0;
            for (int k = n - 1; k >= 0; --k) {
              if (k == i || k == j) continue;
              int kross = cross({x[k], y[kk]}, p, q);
              while (0 <= kk && kk < n && (kross > 0 || ((i < k) == (k < j) && kross == 0))) {
                if (kk != ii && kk != jj) ++cnt;
                kk += incr;
                if (0 <= kk && kk < n) kross = cross({x[k], y[kk]}, p, q);
              }
              way = 1LL * way * cnt % MOD;
              --cnt;
            }
          } else {
            int cnt = 0;
            for (int k = 0; k < n; ++k) {
              if (k == i || k == j) continue;
              int kross = cross({x[k], y[kk]}, p, q);
              while (0 <= kk && kk < n && (kross > 0 || ((i < k) == (k < j) && kross == 0))) {
                if (kk != ii && kk != jj) ++cnt;
                kk += incr;
                if (0 <= kk && kk < n) kross = cross({x[k], y[kk]}, p, q);
              }
              way = 1LL * way * cnt % MOD;
              --cnt;
            }
          }

          // cerr << way << " " << i + 1 << " " << ii + 1 << " " << j + 1 << " " << jj + 1 << " " << cross({0, 0}, p, q) << endl;
          ans = (ans + 1LL * way * cross({0, 0}, p, q)) % MOD;
        }
      }
    }
  }

  if (ans < 0) ans += MOD;
  printf("%d\n", ans);
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    solve();
  }
  return 0;
}