#include <iostream>
#include <cstdlib>
#include <chrono>
#include <climits>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

// Node structure to store data in the linked list
struct node {
    long long int data;  // Data stored in the node
    node* next;          // Pointer to the next node
};

// Head of the linked list
node* head = NULL;

// Function to create a new node
node* create_node(long long int value) {
    node* new_node = new node();
    if (!new_node) {
        cerr << "Memory allocation failed!" << endl;
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a node at the beginning
void insert_at_beginning(long long int value) {
    node* new_node = create_node(value);
    new_node->next = head;
    head = new_node;
}

// Function to print the linked list
void print_list() {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->data;
        if (temp->next != NULL) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Function to get the value at a specific index
long long int node_value_at(int index) {
    node* temp = head;
    int counter = 0;
    while (temp != NULL && counter < index) {
        temp = temp->next;
        counter++;
    }
    if (temp == NULL) {
        return -1;  // Index out of bounds
    }
    return temp->data;
}

// Selection Sort implementation
void selection_sort() {
    for (node* start = head; start != nullptr; start = start->next) {
        node* min_node = start;
        for (node* curr = start->next; curr != nullptr; curr = curr->next) {
            if (curr->data < min_node->data) {
                min_node = curr;
            }
        }
        if (min_node != start) {
            long long int temp = start->data;
            start->data = min_node->data;
            min_node->data = temp;
        }
    }
}

// Split function for Merge Sort
node* split(node* head) {
    if (head == nullptr || head->next == nullptr) 
        return nullptr;
    
    node* fast = head->next;
    node* slow = head;
    
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    node* second_half = slow->next;
    slow->next = nullptr;
    return second_half;
}

// Merge function for Merge Sort
node* merge(node* first, node* second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;
    
    if (first->data < second->data) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

// Merge Sort implementation
node* merge_sort(node* head) {
    if (head == nullptr || head->next == nullptr) 
        return head;
    
    node* second = split(head);
    head = merge_sort(head);
    second = merge_sort(second);
    return merge(head, second);
}

// Middle node finder for Binary Search
node* middle(node* start, node* last) {
    if (start == nullptr) 
        return nullptr;
    
    node* slow = start;
    node* fast = start->next;
    
    while (fast != last) {
        fast = fast->next;
        if (fast != last) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

// Binary Search implementation
void binary_search(long long int value) {
    node* start = head;
    node* last = nullptr;
    bool found = false;

    while (start != last) {
        node* mid = middle(start, last);
        if (mid == nullptr) {
            cout << "Value not found" << endl;
            return;
        }
        
        if (mid->data == value) {
            cout << "Value found in the list" << endl;
            found = true;
            break;
        } else if (mid->data < value) {
            start = mid->next;
        } else {
            last = mid;
        }
    }
    
    if (!found && (last == nullptr || last->data != value)) {
        cout << "Value not found" << endl;
    }
}

// Exponential Search implementation
void exponential_search(long long int value) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    // If first element is the target
    if (head->data == value) {
        cout << "Value found at the beginning of the list" << endl;
        return;
    }

    // Find range for binary search
    int i = 1;
    node* current = head->next;
    node* prev = head;
    
    while (current != nullptr && current->data <= value) {
        prev = current;
        i *= 2;
        // Move forward i steps or until end of list
        for (int j = 0; j < i && current != nullptr; j++) {
            current = current->next;
        }
    }

    // Now perform binary search between prev and current (or end of list)
    node* start = head;
    node* end = current;
    
    // Find the actual bounds
    node* lower = head;
    node* upper = current;
    if (upper == nullptr) {
        // Find the last node if we reached the end
        upper = head;
        while (upper->next != nullptr) {
            upper = upper->next;
        }
    }

    // Perform binary search between lower and upper
    bool found = false;
    while (lower != upper && lower != nullptr) {
        node* mid = middle(lower, upper);
        if (mid == nullptr) break;
        
        if (mid->data == value) {
            cout << "Value found in the list" << endl;
            found = true;
            break;
        } else if (mid->data < value) {
            lower = mid->next;
        } else {
            upper = mid;
        }
    }
    
    if (!found && (upper != nullptr && upper->data == value)) {
        cout << "Value found in the list" << endl;
    } else if (!found) {
        cout << "Value not found" << endl;
    }
}

// User input and menu system
void user_input() {
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
            long long int num = stoll(input);
            insert_at_beginning(num);
        } catch (...) {
            cout << "Invalid input. Please enter a number or 'done'." << endl;
        }
    }

    while (true) {
        cout << "\nWhat action would you like to perform on the list?" << endl;
        cout << "1. Add more elements." << endl;
        cout << "2. Sort the list using Selection Sort" << endl;
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
            case 1: {
                cout << "\nEnter numbers one by one. Type 'done' when finished." << endl;
                while (true) {
                    cout << "Enter a number: ";
                    cin >> input;
                    if (input == "done") {
                        cout << "Input complete.\n" << endl;
                        break;
                    }
                    try {
                        long long int num = stoll(input);
                        insert_at_beginning(num);
                    } catch (...) {
                        cout << "Invalid input. Please enter a number or 'done'." << endl;
                    }
                }
                break;
            }
            
            case 2: {
                auto start_time = high_resolution_clock::now();
                selection_sort();
                auto end_time = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end_time - start_time);
                cout << "\nThe list has been sorted using Selection Sort." << endl;
                cout << "Time taken: " << duration.count() / 1e6 << " ms\n" << endl;
                break;
            }
            
            case 3: {
                auto start_time = high_resolution_clock::now();
                head = merge_sort(head);
                auto end_time = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end_time - start_time);
                cout << "\nThe list has been sorted using Merge Sort." << endl;
                cout << "Time taken: " << duration.count() / 1e6 << " ms\n" << endl;
                break;
            }
            
            case 4: {
                long long int value;
                cout << "Enter value to search: ";
                cin >> value;
                auto start_time = high_resolution_clock::now();
                binary_search(value);
                auto end_time = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end_time - start_time);
                cout << "Time taken: " << duration.count() / 1e6 << " ms\n" << endl;
                break;
            }
            
            case 5: {
                long long int value;
                cout << "Enter value to search: ";
                cin >> value;
                auto start_time = high_resolution_clock::now();
                exponential_search(value);
                auto end_time = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end_time - start_time);
                cout << "Time taken: " << duration.count() / 1e6 << " ms\n" << endl;
                break;
            }
            
            case 6: {
                print_list();
                break;
            }
            
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main() {
    user_input();
    return 0;
}