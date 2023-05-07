// ty __ea for your very clean solution (omg too clean)

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100011
#define MAXQ 200011

int N, Q, arr[MAXN], lim[MAXN];
vector<int> adj[MAXN][30];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        cin >> N >> Q;
        for (int i = 1; i <= N; i++)
            lim[i] = (1 << 30) - 1;
        for (int i = 0; i < Q; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            
            lim[a] &= c;
            lim[b] &= c;
            
            if (a > b)
                swap(a, b);
            else if (a == b) {
                arr[a] = c;
                continue;
            }
            
            for (int j = 0; j < 30; j++) {
                if (c & (1 << j)) {
                    adj[a][j].push_back(b);
                }
            }
        }
        
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 30; j++) {
                for (int k : adj[i][j]) {
                    if ((lim[k] & (1 << j)) == 0) {
                        arr[i] |= (1 << j);
                        break;
                    }
                }
                
                if ((arr[i] & (1 << j)) == 0) {
                    for (int k : adj[i][j]) {
                        arr[k] |= (1 << j);
                    }
                }
            }
            
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}