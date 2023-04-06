// https://codeforces.com/contest/1593/submission/131983798
// not as fast as backtrack, but faster to implement (bitmask bit i = 0 = R, 1 = B)

#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
 
    int test = 1;
    cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        int n, A, B; cin>>n>>A>>B;
        string s; cin>>s;
        int arr[n+1];
        for (int i = 0; i < n; ++i)
        {
            arr[i+1] = s[i] - '0';
        }

        bool dp[n+1][n+1][A][B]; //2nd n : number of red
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k < A; ++k) {
                    for (int l = 0; l < B; ++l) {
                        dp[i][j][k][l] = false;
                    }
                }
            }
        }

        dp[1][1][arr[1]%A][0] = true;
        dp[1][0][0][arr[1]%B] = true;

        for (int i = 1; i <= n-1; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k < A; ++k) {
                    for (int l = 0; l < B; ++l) {
                        if (dp[i][j][k][l] == true) {
                            dp[i+1][j+1][(arr[i+1]+k*10)%A][l] = true;
                            dp[i+1][j][k][(arr[i+1]+l*10)%B] = true;
                        }
                    }
                }
            }
        }

        bool flag = false;
        int red;
        for (int j = n/2; j >= 1; --j) {
            if (dp[n][j][0][0] == true || dp[n][n-j][0][0] == true) {
                flag = true;
                red = (dp[n][j][0][0] == true) ? j : n-j;
                break;
            }
        }

        if (flag == false) {
            cout<<-1<<endl;
            continue;
        }

        int rA = 0, rB = 0;
        string ans = "";
        for (int i = n; i >= 2 ; --i) {
            bool findR = false;
            if (red > 0) {
                for (int k = 0; k < A; ++k) {
                    if ((10*k+arr[i]) % A == rA && dp[i-1][red-1][k][rB] == true) {
                        findR = true;
                        --red;
                        rA = k;
                        ans += 'R';
                        break;
                    }
                }
            }

            if (findR == false) {
                for (int l = 0; l < B; ++l) {
                    if ((10*l+arr[i]) % B == rB && dp[i-1][red][rA][l] == true) {
                        rB = l;
                        ans += 'B';
                        break;
                    }
                }
            }
        }

        if (red == 1) ans += 'R';
        else ans += 'B';

        reverse(ans.begin(), ans.end());
        cout<<ans<<endl;

    }

    return 0;
}
