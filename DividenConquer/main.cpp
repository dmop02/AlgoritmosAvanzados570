//Domingo Mora 
// Alvaro Solano
// Divide & Conquer

#include <iostream>
#include <vector>
using namespace std;

// Function to print the array
// Complexity: O(n)
void printArray(const vector<double>& arr) {
    for (double num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Function to merge two halves of the array
// Complexity: O(n)
void merge(vector<double>& arr, int low, int mid, int high) {
    int lengthLeft = mid - low + 1;
    int lengthRight = high - mid;

    vector<double> arrLeft(lengthLeft), arrRight(lengthRight);

    for (int a = 0; a < lengthLeft; a++) {
        arrLeft[a] = arr[low + a];
    }
    for (int a = 0; a < lengthRight; a++) {
        arrRight[a] = arr[mid + 1 + a];
    }

    int i = 0, j = 0, k = low;

    while (i < lengthLeft && j < lengthRight) {
        if (arrLeft[i] >= arrRight[j]) {
            arr[k] = arrLeft[i];
            i++;
        } else {
            arr[k] = arrRight[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left array
    while (i < lengthLeft) {
        arr[k] = arrLeft[i];
        k++;
        i++;
    }

    // Copy remaining elements of right array
    while (j < lengthRight) {
        arr[k] = arrRight[j];
        k++;
        j++;
    }
}

// Function to perform merge sort
// Complexity: O(n log n)
void mergeSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    cout << "Enter the number of elements: ";
    int n;
    cin >> n;

    vector<double> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Array before mergeSort() : ";
    printArray(arr);

    mergeSort(arr, 0, n - 1);

    cout << "Array in descending order : ";
    printArray(arr);

    return 0;
}
