#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

// Node structure for linked list
struct node {
    long long int data;
    node* next;
};

node* head = nullptr;

// Utility functions
node* create_node(long long int value) {
    node* new_node = new node();
    new_node->data = value;
    new_node->next = nullptr;
    return new_node;
}

void insert_at_beginning(long long int value) {
    node* new_node = create_node(value);
    new_node->next = head;
    head = new_node;
}

void print_list() {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> nullptr" << endl;
}

void clear_list() {
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

// 1. Generate N random numbers (clears previous list)
void generate_random_numbers(int N, int min_val = 1, int max_val = 10000) {
    if (N <= 0) {
        cout << "Please enter a positive number for N." << endl;
        return;
    }

    clear_list();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min_val, max_val);

    for (int i = 0; i < N; ++i) {
        insert_at_beginning(dist(gen));
    }
}

// 2. Quick Sort implementation for linked list
node* get_tail(node* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

node* partition(node* head, node* end, node** new_head, node** new_end) {
    node* pivot = end;
    node* prev = nullptr;
    node* cur = head;
    node* tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if (*new_head == nullptr) *new_head = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            node* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (*new_head == nullptr) *new_head = pivot;
    *new_end = tail;

    return pivot;
}

node* quick_sort_recur(node* head, node* end) {
    if (!head || head == end)
        return head;

    node* new_head = nullptr;
    node* new_end = nullptr;

    node* pivot = partition(head, end, &new_head, &new_end);

    if (new_head != pivot) {
        node* tmp = new_head;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;

        new_head = quick_sort_recur(new_head, tmp);

        tmp = get_tail(new_head);
        tmp->next = pivot;
    }

    pivot->next = quick_sort_recur(pivot->next, new_end);

    return new_head;
}

void quick_sort() {
    head = quick_sort_recur(head, get_tail(head));
}

// 3. Merge Sort implementation
node* split(node* head) {
    node* slow = head;
    node* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    node* second = slow->next;
    slow->next = nullptr;
    return second;
}

node* merge(node* first, node* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

node* merge_sort(node* head) {
    if (!head || !head->next) return head;

    node* second = split(head);

    head = merge_sort(head);
    second = merge_sort(second);

    return merge(head, second);
}

// 4. Searching algorithms

// Find middle node between start and end (not including end)
node* middle(node* start, node* end) {
    if (!start) return nullptr;

    node* slow = start;
    node* fast = start->next;

    while (fast != end) {
        fast = fast->next;
        if (fast != end) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

// Binary search on sorted linked list
void binary_search(long long int value, bool silent = false) {
    node* start = head;
    node* end = nullptr;

    while (start != end) {
        node* mid = middle(start, end);
        if (!mid) break;

        if (mid->data == value) {
            if (!silent) cout << "Value found." << endl;
            return;
        } else if (mid->data < value) {
            start = mid->next;
        } else {
            end = mid;
        }
    }

    if (!silent) cout << "Value not found." << endl;
}

// Exponential search on sorted linked list
void exponential_search(long long int value, bool silent = false) {
    if (!head) {
        if (!silent) cout << "List is empty." << endl;
        return;
    }

    if (head->data == value) {
        if (!silent) cout << "Value found at head." << endl;
        return;
    }

    int i = 1;
    node* current = head->next;

    while (current && current->data <= value) {
        i *= 2;
        for (int j = 0; j < i && current != nullptr; j++) {
            current = current->next;
        }
    }

    node* start = head;
    node* end = current;

    while (start != end) {
        node* mid = middle(start, end);
        if (!mid) break;

        if (mid->data == value) {
            if (!silent) cout << "Value found." << endl;
            return;
        } else if (mid->data < value) {
            start = mid->next;
        } else {
            end = mid;
        }
    }

    if (!silent) cout << "Value not found." << endl;
}

// 5. Runtime analysis for multiple input sizes
void run_analysis() {
    vector<int> test_sizes = {100, 1000, 5000, 10000};

    cout << "\nRuntime Analysis (times in milliseconds)\n";
    cout << "---------------------------------------\n";
    cout << "N\tQuick Sort\tMerge Sort\tBinary Search\tExponential Search\n";

    for (int N : test_sizes) {
        generate_random_numbers(N);

        auto start = high_resolution_clock::now();
        quick_sort();
        auto qs_time = duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000.0;

        generate_random_numbers(N);
        start = high_resolution_clock::now();
        head = merge_sort(head);
        auto ms_time = duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000.0;

        // Prepare sorted list for searching
        generate_random_numbers(N);
        head = merge_sort(head);
        long long int search_val = head->data;  // Value guaranteed to exist

        start = high_resolution_clock::now();
        binary_search(search_val, true);  // silent mode
        auto bs_time = duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000.0;

        start = high_resolution_clock::now();
        exponential_search(search_val, true);  // silent mode
        auto es_time = duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000.0;

        printf("%d\t%.4f\t\t%.4f\t\t%.4f\t\t%.4f\n", N, qs_time, ms_time, bs_time, es_time);
    }
}

// 6. Time Complexity Summary (for reference)
/*
Algorithm      Best Case   Average Case   Worst Case   Space Complexity
----------------------------------------------------------------------
Quick Sort     O(n log n)  O(n log n)     O(n^2)       O(log n)
Merge Sort     O(n log n)  O(n log n)     O(n log n)   O(n)
Binary Search  O(1)        O(log n)       O(log n)     O(1)
Exponential    O(1)        O(log i)       O(log n)     O(1)
Search                   (i = target index)
*/

// 7. User Interface menu
void show_menu() {
    cout << "\nMenu Options:\n";
    cout << "1. Generate random numbers\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "4. Binary Search\n";
    cout << "5. Exponential Search\n";
    cout << "6. Print list\n";
    cout << "7. Run complete runtime analysis\n";
    cout << "8. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    while (true) {
        show_menu();
        cin >> choice;

        if (choice == 8) break;

        switch (choice) {
            case 1: {
                int N;
                cout << "Enter number of random values to generate: ";
                cin >> N;
                generate_random_numbers(N);
                cout << N << " random numbers generated.\n";
                break;
            }
            case 2: {
                if (!head) {
                    cout << "List is empty. Generate numbers first.\n";
                    break;
                }
                auto start = high_resolution_clock::now();
                quick_sort();
                auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
                cout << "Quick Sort completed in " << duration.count() / 1000.0 << " ms\n";
                break;
            }
            case 3: {
                if (!head) {
                    cout << "List is empty. Generate numbers first.\n";
                    break;
                }
                auto start = high_resolution_clock::now();
                head = merge_sort(head);
                auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
                cout << "Merge Sort completed in " << duration.count() / 1000.0 << " ms\n";
                break;
            }
            case 4: {
                if (!head) {
                    cout << "List is empty. Generate numbers first.\n";
                    break;
                }
                long long int val;
                cout << "Enter value to search: ";
                cin >> val;
                auto start = high_resolution_clock::now();
                binary_search(val);
                auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
                cout << "Binary Search completed in " << duration.count() / 1000.0 << " ms\n";
                break;
            }
            case 5: {
                if (!head) {
                    cout << "List is empty. Generate numbers first.\n";
                    break;
                }
                long long int val;
                cout << "Enter value to search: ";
                cin >> val;
                auto start = high_resolution_clock::now();
                exponential_search(val);
                auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
                cout << "Exponential Search completed in " << duration.count() / 1000.0 << " ms\n";
                break;
            }
            case 6: {
                if (!head) {
                    cout << "List is empty. Nothing to print.\n";
                } else {
                    print_list();
                }
                break;
            }
            case 7: {
                run_analysis();
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    clear_list();
    return 0;
}
