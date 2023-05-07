// with 2 queries ?n+1 ?n+2 we can build a chain through all vertice
// after that it's just case work

#include<bits/stdc++.h>
 
using namespace std;

int add(int k) {
    cout << "+ " << k << endl;
    int x; 
    cin >> x;
    return x;
}

int ask(int i, int j) {
    cout << "? " << i << ' ' << j << endl;
    int x;
    cin >> x;
    return x; 
}

void solve() {
    int n;
    cin >> n;

    if (n == 2) {
        cout << "! 1 2 2 1" << endl;
        int x;
        cin >> x;
        return;
    }

    int res = add(n+1);
    if (res == -2) return;
    res = add(n+2);
    if (res == -2) return;

    int tree[n+1];
    int cur = 1;
    for (int i = 1; i <= n; i += 2) {
        tree[i] = cur;
        cur++;
    }
    cur = n;
    for (int i = 2; i <= n; i += 2) {
        tree[i] = cur;
        cur--;
    }

    pair<int,int> dist[n+1];
    int mx = 0;
    int neigh = -1;
    for (int i = 2; i <= n; ++i) {
        int res = ask(1, i);
        if (res == -2) return;

        mx = max(mx, res);
        dist[i].first = res;

        if (res == 1) neigh = i;
    }

    int mx2 = 0;
    for (int i = 2; i <= n; ++i) {
        if (i == neigh) continue;

        int res = ask(neigh, i);
        if (res == -2) return;

        mx2 = max(mx2, res);
        dist[i].second = res;
    }

    int ind[2][n+1];
    ind[0][1] = n-mx; ind[1][1] = mx+1;
    ind[0][neigh] = (mx2 <= mx) ? n-mx+1 : n-mx-1;
    ind[1][neigh] = (mx2 <= mx) ? mx : mx+2;

    for (int i = 1; i <= n; ++i) {
        if (i == 1 || i == neigh) continue;

        int dist1 = dist[i].first, dist2 = dist[i].second;
        if (dist1 < dist2) {
            if (ind[0][1] < ind[0][neigh]) {
                ind[0][i] = ind[0][1] - dist1;
                ind[1][i] = ind[1][1] + dist1;
            } else {
                ind[0][i] = ind[0][1] + dist1;
                ind[1][i] = ind[1][1] - dist1;
            }
        } else {
            if (ind[0][1] < ind[0][neigh]) {
                ind[0][i] = ind[0][1] + dist1;
                ind[1][i] = ind[1][1] - dist1;
            } else {
                ind[0][i] = ind[0][1] - dist1;
                ind[1][i] = ind[1][1] + dist1;
            }
        }
    }

    cout << "!";
    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << ' ' << tree[ind[i][j]];
        }
    } cout << endl;

    cin >> res;
    if (res == -2) return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }

    return 0;
}
