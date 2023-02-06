#include <iostream>

using namespace std;

// Definition for a node in the linked list
struct Node {
    int data;
    Node *next;
};

// Pointer to the front node in the linked list
Node *front = NULL;

// Pointer to the last node in the linked list
Node *rear = NULL;

// Function to insert an element into the queue
void insert(int value) {
    // Create a new node
    Node *temp = new Node;
    temp->data = value;
    temp->next = NULL;

    // If the linked list is empty, set both front and rear pointers to the new node
    if (front == NULL && rear == NULL) {
        front = rear = temp;
        return;
    }

    // Update the next pointer of the last node to point to the new node
    rear->next = temp;

    // Update the rear pointer to point to the new node
    rear = temp;
}

// Function to delete an element from the queue
void deletion() {
    // If the linked list is empty, return
    if (front == NULL) {
        cout << "The queue is empty" << endl;
        return;
    }

    // Store the pointer to the front node in a temporary variable
    Node *temp = front;

    // Update the front pointer to point to the next node
    front = front->next;

    // Free the memory occupied by the node to be deleted
    delete temp;
}

// Function to display the elements in the queue
void display() {
    // If the linked list is empty, return
    if (front == NULL) {
        cout << "The queue is empty" << endl;
        return;
    }

    // Store the pointer to the front node in a temporary variable
    Node *temp = front;

    // Traverse the linked list and print the data of each node
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main() {
    // Declare a variable to store the user's choice
    int choice;

    // Run an infinite loop until the user chooses to exit
    while (true) {
        // Print the menu options
        cout << "1. Insert an element into the queue" << endl;
        cout << "2. Delete an element from the queue" << endl;
        cout << "3. Display the elements in the queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        // Read the user's choice
        cin >> choice;

        // Perform the corresponding operation based on the user's choice
        switch (choice) {
            case 1: // Insert an element into the queue
                int value;
                cout << "Enter the value to be inserted: ";
                cin >> value;
                insert(value);
                break;
            case 2: // Delete an element from the queue
                deletion();
                break;
            case 3: // Display the elements in the queue
                display();
                break;
            case 4: // Exit
                exit(0);
                        break;
            default: // Invalid choice
                cout << "Invalid choice, try again" << endl;
                break;
        }
    }

    return 0;
}

