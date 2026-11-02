#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(vector<int>& a, int low, int high, int& count) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        count++;

        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int>& a, int low, int high,
               bool random, int& count) {
    if (low >= high)
        return;

    if (random) {
        int p = low + rand() % (high - low + 1);
        swap(a[p], a[high]);
    }

    int p = partition(a, low, high, count);

    quickSort(a, low, p - 1, random, count);
    quickSort(a, p + 1, high, random, count);
}

void test(vector<int> a, string type, bool random) {
    int count = 0;

    clock_t start = clock();

    quickSort(a, 0, a.size() - 1, random, count);

    double time = double(clock() - start) / CLOCKS_PER_SEC;

    cout << type << "\t"
         << (random ? "Randomized" : "Deterministic")
         << "\t" << count
         << "\t" << time << " sec"
         << "\t" << (is_sorted(a.begin(), a.end()) ? "Yes" : "No")
         << '\n';
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid input.\n";
        return 1;
    }

    srand(time(0));

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        a[i] = i + 1;

    vector<int> sorted = a;

    vector<int> reversed = a;
    reverse(reversed.begin(), reversed.end());

    random_shuffle(a.begin(), a.end());

    cout << "\nInput\t\tVariant\t\tComparisons\tTime\tSorted?\n";

    test(a, "Random", false);
    test(a, "Random", true);

    test(sorted, "Sorted", false);
    test(sorted, "Sorted", true);

    test(reversed, "Reverse", false);
    test(reversed, "Reverse", true);

    return 0;
}