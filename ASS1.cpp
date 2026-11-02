#include <iostream>
#include <ctime>
using namespace std;

int fibonacciIterative(int n) {
    int a = 0, b = 1;

    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }

    return n == 0 ? 0 : b;
}

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter n (0 to 40): ";
    cin >> n;

    if (n < 0 || n > 40) {
        cout << "Invalid input";
        return 1;
    }

    clock_t start = clock();
    int result1 = fibonacciIterative(n);
    double time1 = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    int result2 = fibonacciRecursive(n);
    double time2 = (double)(clock() - start) / CLOCKS_PER_SEC;

    cout << "\nIterative result: " << result1;
    cout << "\nRecursive result: " << result2;
    cout << "\nIterative time: " << time1 << " seconds";
    cout << "\nRecursive time: " << time2 << " seconds\n";

    return 0;
}