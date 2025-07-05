#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace std::chrono;

// Binary Search (Iterative)
int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(const vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    if (arr[0] == target) return 0;
    
    int i = 1;
    while (i < arr.size() && arr[i] <= target) 
        i *= 2;
    
    int low = i / 2;
    int high = min(i, static_cast<int>(arr.size()) - 1);
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Quick Sort helpers
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort helpers
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> data;
    bool isSorted = false;
    string input;

    cout << "Enter numbers one by one. Type 'done' when finished." << endl;
    while (true) {
        cout << "Enter a number: ";
        cin >> input;
        
        if (input == "done") {
            cout << "Input complete.\n" << endl;
            break;
        }
        
        try {
            int num = stoi(input);
            data.push_back(num);
            isSorted = false;
        } catch (...) {
            cout << "Invalid input. Please enter a number or 'done'." << endl;
        }
    }

    while (true) {
        cout << "\nWhat action would you like to perform on the list?" << endl;
        cout << "1. Add more elements." << endl;
        cout << "2. Sort the list using Quick Sort" << endl;
        cout << "3. Sort the list using Merge Sort" << endl;
        cout << "4. Search for an element using Binary Search" << endl;
        cout << "5. Search for an element using Exponential Search" << endl;
        cout << "6. Display the list" << endl;
        cout << "9. Exit the program" << endl;
        cout << "> ";

        int choice;
        cin >> choice;

        if (choice == 9) break;

        switch (choice) {
            case 1: {  // Add elements
                cout << "\nEnter numbers one by one. Type 'done' when finished." << endl;
                cin.ignore();
                while (true) {
                    cout << "Enter a number: ";
                    getline(cin, input);
                    
                    if (input == "done") {
                        cout << "Input complete.\n" << endl;
                        break;
                    }
                    
                    try {
                        int num = stoi(input);
                        data.push_back(num);
                        isSorted = false;
                    } catch (...) {
                        cout << "Invalid input. Please enter a number or 'done'." << endl;
                    }
                }
                break;
            }
            
            case 2: {  // Quick Sort
                if (data.empty()) {
                    cout << "List is empty!" << endl;
                    break;
                }
                
                vector<int> temp = data;
                auto start = high_resolution_clock::now();
                quickSort(temp, 0, temp.size() - 1);
                auto end = high_resolution_clock::now();
                
                data = temp;
                isSorted = true;
                
                double time_taken = duration_cast<nanoseconds>(end - start).count() / 1e6;
                cout << "\nThe list has been sorted using Quick Sort." << endl;
                cout << "Time taken: " << fixed << setprecision(7) << time_taken << " ms\n" << endl;
                break;
            }
            
            case 3: {  // Merge Sort
                if (data.empty()) {
                    cout << "List is empty!" << endl;
                    break;
                }
                
                vector<int> temp = data;
                auto start = high_resolution_clock::now();
                mergeSort(temp, 0, temp.size() - 1);
                auto end = high_resolution_clock::now();
                
                data = temp;
                isSorted = true;
                
                double time_taken = duration_cast<nanoseconds>(end - start).count() / 1e6;
                cout << "\nThe list has been sorted using Merge Sort." << endl;
                cout << "Time taken: " << fixed << setprecision(7) << time_taken << " ms\n" << endl;
                break;
            }
            
            case 4: {  // Binary Search
                if (!isSorted) {
                    cout << "Error: List must be sorted first!" << endl;
                    break;
                }
                
                int target;
                cout << "Enter element to search: ";
                cin >> target;
                
                auto start = high_resolution_clock::now();
                int result = binarySearch(data, target);
                auto end = high_resolution_clock::now();
                
                double time_taken = duration_cast<nanoseconds>(end - start).count() / 1e6;
                
                if (result != -1) {
                    cout << "Element found at index " << result << endl;
                } else {
                    cout << "Element not found in the list" << endl;
                }
                cout << "Time taken: " << fixed << setprecision(7) << time_taken << " ms\n" << endl;
                break;
            }
            
            case 5: {  // Exponential Search
                if (!isSorted) {
                    cout << "Error: List must be sorted first!" << endl;
                    break;
                }
                
                int target;
                cout << "Enter element to search: ";
                cin >> target;
                
                auto start = high_resolution_clock::now();
                int result = exponentialSearch(data, target);
                auto end = high_resolution_clock::now();
                
                double time_taken = duration_cast<nanoseconds>(end - start).count() / 1e6;
                
                if (result != -1) {
                    cout << "Element found at index " << result << endl;
                } else {
                    cout << "Element not found in the list" << endl;
                }
                cout << "Time taken: " << fixed << setprecision(7) << time_taken << " ms\n" << endl;
                break;
            }
            
            case 6: {  // Display list
                if (data.empty()) {
                    cout << "List is empty!" << endl;
                    break;
                }
                
                cout << "\nCurrent list (" << data.size() << " elements): ";
                for (int i = 0; i < data.size(); i++) {
                    cout << data[i];
                    if (i < data.size() - 1) cout << ", ";
                }
                cout << "\n" << endl;
                break;
            }
            
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
