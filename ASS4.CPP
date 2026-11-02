#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items.\n";
        return 1;
    }

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter weight and value of each item:\n";

    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];

        if (weight[i] <= 0 || value[i] < 0) {
            cout << "Invalid weight or value.\n";
            return 1;
        }
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Invalid capacity.\n";
        return 1;
    }

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];

            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    value[i - 1] + dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    cout << "\nMaximum value: " << dp[n][capacity] << '\n';

    vector<int> selected;
    int remaining = capacity;

    for (int i = n; i > 0; i--) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            selected.push_back(i);
            remaining -= weight[i - 1];
        }
    }

    reverse(selected.begin(), selected.end());

    cout << "Selected items: ";

    if (selected.empty())
        cout << "None";

    for (int id : selected)
        cout << id << ' ';

    cout << "\nTotal weight: " << capacity - remaining << '\n';

    return 0;
}