#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void calculateChange(vector<int>& denominations, int price, int paid) {
    sort(denominations.rbegin(), denominations.rend()); // Sort in descending order

    vector<int> change(denominations.size(), 0); // Initialize array to store the number of coins

    int remainingChange = paid - price;
    if (remainingChange < 0) {
        cout << "Insufficient payment. Cannot provide change." << endl;
        return;
    }

    for (size_t i = 0; i < denominations.size(); ++i) {
        if (remainingChange >= denominations[i]) {
            change[i] = remainingChange / denominations[i];
            remainingChange %= denominations[i];
        }
    }

    if (remainingChange > 0) {
        cout << "Cannot provide exact change with the given denominations." << endl;
        return;
    }

    // Output the result
    cout << "Su cambio es de:" << endl;
    for (size_t i = 0; i < denominations.size(); ++i) {
        cout << denominations[i] << " - " << change[i] << " monedas" << endl;
    }
}

int main() {
    int N;
    cout << "Enter the number of coin denominations: ";
    cin >> N;

    vector<int> denominations(N);
    cout << "Enter the coin denominations, one on each line:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> denominations[i];
    }

    int P, Q;
    cout << "Enter the price of the product (P): ";
    cin >> P;
    cout << "Enter the bill/coin used to pay for the product (Q): ";
    cin >> Q;

    calculateChange(denominations, P, Q);

    return 0;
}
