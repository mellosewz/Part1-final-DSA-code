#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

vector<int> numbers;

// ----------- Merge Sort Functions -------------
void merge(vector<int>& a, int l, int m, int r) {
    vector<int> L(a.begin() + l, a.begin() + m + 1);
    vector<int> R(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = l;

    // Merge the two sorted halves
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    // Copy remaining elements
    while (i < L.size()) a[k++] = L[i++];
    while (j < R.size()) a[k++] = R[j++];
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

// ----------- Binary Search Function -------------
int binarySearch(vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// ----------- Exponential Search Function -------------
int exponentialSearch(vector<int>& a, int x) {
    if (a.empty()) return -1;
    if (a[0] == x) return 0;

    int i = 1;
    // Find range where the element may exist
    while (i < a.size() && a[i] <= x) i *= 2;

    int l = i / 2;
    int r = min(i, (int)a.size() - 1);

    // Binary Search within the found range
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// ----------- Display Function -------------
void displayList() {
    if (numbers.empty()) {
        cout << "The list is empty.\n";
        return;
    }
    cout << "List elements: ";
    for (int num : numbers) cout << num << " ";
    cout << "\n";
}

// ----------- Menu Function -------------
void showMenu() {
    cout << "\nWhat action would you like to perform on the list?\n";
    cout << "1. Add more elements.\n";
    cout << "2. Sort the list using Selection Sort. [Not implemented]\n";
    cout << "3. Sort the list using Merge Sort.\n";
    cout << "4. Search for an element using Binary Search.\n";
    cout << "5. Search for an element using Exponential Search.\n";
    cout << "6. Display the list.\n";
    cout << "0. Exit the program\n";
    cout << ">\n";
}

// ----------- Main Program -------------
int main() {
    string input;
    cout << "Enter a number: ";

    // Input elements until "done"
    while (cin >> input && input != "done") {
        try {
            int num = stoi(input);
            numbers.push_back(num);
            cout << "Enter a number: ";
        } catch (...) {
            cout << "Invalid input. Enter a number or type 'done': ";
        }
    }

    cout << "Input complete.\n";

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add more numbers
                cout << "Enter a number: ";
                while (cin >> input && input != "done") {
                    try {
                        int num = stoi(input);
                        numbers.push_back(num);
                        cout << "Enter a number: ";
                    } catch (...) {
                        cout << "Invalid input. Enter a number or type 'done': ";
                    }
                }
                cout << "Input complete.\n";
                break;
            }

            case 2: {
                // Selection sort not implemented
                cout << "Selection Sort not implemented.\n";
                break;
            }

            case 3: {
                // Perform Merge Sort
                if (numbers.empty()) {
                    cout << "List is empty.\n";
                    break;
                }
                auto start = high_resolution_clock::now();
                mergeSort(numbers, 0, numbers.size() - 1);
                auto end = high_resolution_clock::now();
                duration<double, milli> time = end - start;

                cout << "The list has been sorted using Merge Sort.\n";
                cout << "Time taken: " << time.count() << " ms\n";
                break;
            }

            case 4: {
                // Binary Search
                if (numbers.empty()) {
                    cout << "List is empty.\n";
                    break;
                }
                int key;
                cout << "Enter element to search: ";
                cin >> key;
                auto start = high_resolution_clock::now();
                int index = binarySearch(numbers, key);
                auto end = high_resolution_clock::now();
                duration<double, milli> time = end - start;

                if (index != -1)
                    cout << "Element found at index: " << index << "\n";
                else
                    cout << "Element not found.\n";

                cout << "Time taken: " << time.count() << " ms\n";
                break;
            }

            case 5: {
                // Exponential Search
                if (numbers.empty()) {
                    cout << "List is empty.\n";
                    break;
                }
                int key;
                cout << "Enter element to search: ";
                cin >> key;
                auto start = high_resolution_clock::now();
                int index = exponentialSearch(numbers, key);
                auto end = high_resolution_clock::now();
                duration<double, milli> time = end - start;

                if (index != -1)
                    cout << "Element found at index: " << index << "\n";
                else
                    cout << "Element not found.\n";

                cout << "Time taken: " << time.count() << " ms\n";
                break;
            }

            case 6: {
                // Display the current list
                displayList();
                break;
            }

            case 0: {
                // Exit the program
                cout << "Exiting...\n";
                break;
            }

            default: {
                cout << "Invalid choice.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
