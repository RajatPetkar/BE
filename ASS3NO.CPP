#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    int id;
    double weight, value;
};

double knapsack(vector<Item>& items, double capacity) {
    sort(items.begin(), items.end(), [](Item a, Item b) {
        return a.value / a.weight > b.value / b.weight;
    });

    double total = 0;

    cout << "\nItem\tFraction\tWeight\t\tValue\n";

    for (Item item : items) {
        if (capacity <= 0)
            break;

        double weightTaken = min(item.weight, capacity);
        double fraction = weightTaken / item.weight;
        double valueGained = fraction * item.value;

        capacity -= weightTaken;
        total += valueGained;

        cout << item.id << '\t' << fraction << "\t\t"
             << weightTaken << "\t\t" << valueGained << '\n';
    }

    return total;
}

int main() {
    int n;
    double capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items.\n";
        return 1;
    }

    vector<Item> items(n);

    cout << "Enter weight and value of each item:\n";

    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        cin >> items[i].weight >> items[i].value;

        if (items[i].weight <= 0 || items[i].value < 0) {
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

    cout << fixed << setprecision(2);

    cout << "\nMaximum value: "
         << knapsack(items, capacity) << '\n';

    return 0;
}