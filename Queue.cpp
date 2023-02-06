#include <iostream>
using namespace std;

// Define a macro constant for the maximum size of the queue
#define MAX_SIZE 100

// Declare an integer array for the queue
int queue[MAX_SIZE];

// Declare variables to keep track of the front and rear of the queue
int front = 0, rear = -1;

// Function to insert a value into the queue
void insert(int value)
{
    // Check if the queue is full
    if (rear == MAX_SIZE - 1)
    {
        // If the queue is full, print an error message
        cout << "Queue is full, cannot insert " << value << endl;
    }
    else
    {
        // If the queue is not full, increment the rear index
        rear++;
        // Insert the value at the rear of the queue
        queue[rear] = value;
        // Print a message indicating that the value has been inserted
        cout << value << " inserted into the queue" << endl;
    }
}

// Function to delete a value from the queue
void deletion()
{
    // Check if the queue is empty
    if (rear == -1)
    {
        // If the queue is empty, print an error message
        cout << "Queue is empty, nothing to delete" << endl;
    }
    else
    {
        // If the queue is not empty, store the front value in a variable
        int value = queue[front];
        // Increment the front index
        front++;
        // Print a message indicating that the value has been deleted
        cout << value << " deleted from the queue" << endl;
    }
}

// Function to display the values in the queue
void display()
{
    // Check if the queue is empty
    if (rear == -1)
    {
        // If the queue is empty, print an error message
        cout << "Queue is empty, nothing to display" << endl;
    }
    else
    {
        // If the queue is not empty, print the values in the queue
        cout << "Values in the queue are: ";
        for (int i = front; i <= rear; i++)
        {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
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
