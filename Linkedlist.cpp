#include <iostream>
using namespace std;

// Structure to define a node in the linked list
struct Node
{
    int data;
    Node *next;
};

// Pointer to the front (head) of the linked list
Node *front = NULL;

// Pointer to the end (tail) of the linked list
Node *rear = NULL;

// Function to insert an element into the linked list (queue)
void insert(int value)
{
    // Allocate a new node in the memory
    Node *newNode = new Node;

    // Store the value in the new node
    newNode->data = value;

    // Set the next pointer of the new node to NULL
    newNode->next = NULL;

    // If the linked list is empty, set the front and rear pointers to the new node
    if (front == NULL && rear == NULL)
    {
        front = rear = newNode;
        return;
    }

    // Add the new node to the end (rear) of the linked list
    rear->next = newNode;
    rear = newNode;
}

// Function to delete an element from the linked list (queue)
void deletion(int position)
{
    // If the linked list is empty, return
    if (front == NULL)
    {
        cout << "The linked list is empty" << endl;
        return;
    }

    // Store the pointer to the front node in a temporary variable
    Node *temp = front;

    // If the user wants to delete the first node, set the front pointer to the next node
    if (position == 1)
    {
        front = temp->next;
        delete temp;
        return;
    }

    // Traverse the linked list to find the node at the specified position
    for (int i = 0; temp != NULL && i < position - 2; i++)
    {
        temp = temp->next;
    }

    // If the specified position is greater than the number of nodes in the linked list, return
    if (temp == NULL || temp->next == NULL)
    {
        cout << "The specified position is not available in the linked list" << endl;
        return;
    }

    // Store the pointer to the node to be deleted in a temporary variable
    Node *next = temp->next->next;

    // Free the memory occupied by the node to be deleted
    delete temp->next;

    // Update the next pointer of the previous node to point to the next node
    temp->next = next;
}

// Function to display the elements in the linked list (queue)
void display()
{
    // If the linked list is empty, return
    if (front == NULL)
    {
        cout << "The queue is empty" << endl;
        return;
    }

    // Create a pointer to traverse the linked list
    Node *ptr = front;

    // Traverse the linked list and print the elements
    while (ptr != NULL)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

int main()
{
    // Declare a variable to store the user's choice
    int choice;

    // Run an infinite loop until the user chooses to exit
    while (true)
    {
        // Print the menu options
        cout << "1. Insert an element into the queue" << endl;
        cout << "2. Delete an element from the queue" << endl;
        cout << "3. Display the elements in the queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        // Read the user's choice
        cin >> choice;

        // Perform the corresponding operation based on the user's choice
        switch (choice)
        {
        case 1: // Insert an element into the queue
            int value;
            cout << "Enter the value to be inserted: ";
            cin >> value;
            insert(value);
            break;
        case 2: // Delete an element from the queue
            int position;
            cout << "Enter the position of the element to be deleted: ";
            cin >> position;
            deletion(position);
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
