#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void printVector(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

// Function to merge two halves of the array and count inversions
int mergeAndCount(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    int i = 0, j = 0;
    int k = l;
    int inv_count = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            inv_count += (n1 - i);
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    return inv_count;
}

// Function to recursively divide the array and count inversions
int mergeSortAndCount(vector<int>& arr, int l, int r) {
    int inv_count = 0;
    if (l < r) {
        int m = l + (r - l) / 2;

        // Count inversions in left and right halves
        inv_count += mergeSortAndCount(arr, l, m);
        inv_count += mergeSortAndCount(arr, m + 1, r);

        // Merge the two halves and count inversions
        inv_count += mergeAndCount(arr, l, m, r);
    }
    return inv_count;
}

int compute(vector<int>& perm, int n) {
    return mergeSortAndCount(perm, 0, n - 1);
}

int main() {
    vector<int> perm;

    int z, n, m;
    cin >> z;
    while (z) {
        perm.clear();
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            perm.push_back(x);
        }
        int sol = compute(perm, n);
        cout << sol << "\n";
        z--;
    }
    return 1;
}