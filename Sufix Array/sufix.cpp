#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> suffixArrayNaive(string S) {
    int n = S.length();
    vector<string> sa;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        sa.push_back(S.substr(n - i - 1, i + 1));
    sort(sa.begin(), sa.end());
    for (int i = 0; i < n; i++)
        A[i] = n - sa[i].size() + 1;
    return A;
}

int main() {
    string input;
    cout << "Enter a string:";
    getline(cin, input);

    vector<int> result = suffixArrayNaive(input);

    cout << "Suffix Array: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
