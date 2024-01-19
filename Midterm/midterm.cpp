#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int m, vector<int> &holes) {
    vector<int> dp(n, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        if (holes[i] == 1) {
            for (int j = i + 1; j <= min(n - 1, i + 6); ++j) {
                dp[j] = (dp[j] + dp[i]) % m;
            }
        } 
    }

    return dp[n - 1] % m;
}

int main() {
    int z;
    cin >> z;

    while (z--) {
        int n, m;
        cin >> n >> m;

        vector<int> holes(n);
        for (int i = 0; i < n; ++i) {
            cin >> holes[i];
        }

        cout << solve(n, m, holes) << endl;
    }

    return 0;
}