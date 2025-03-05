#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int val)
    {
        data = val;
        next = nullptr;
    }
};

class Stack
{
public:
    Node *top;

    Stack()
    {
        top = nullptr;
    }

    void push(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (top == nullptr)
        {
            cout << "Stack Underflow!" << endl;
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    int peek()
    {
        if (top == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void merge(Stack &s2)
    {
        if (s2.top == nullptr)
            return; // If s2 is empty, no merging needed
        Node *temp = s2.top;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = top; // Link last node of s2 to top of s1
        top = s2.top;     // Update top pointer to new merged top
        s2.top = nullptr; // Empty s2 after merging
    }

    void printStack()
    {
        Node *temp = top;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "END" << endl;
    }
};

int main()
{
    Stack s1, s2;

    s1.push(10);
    s1.push(20);
    s1.push(30);

    s2.push(40);
    s2.push(50);
    s2.push(60);

    cout << "Stack 1 before merge: ";
    s1.printStack();

    cout << "Stack 2 before merge: ";
    s2.printStack();

    s1.merge(s2);

    cout << "Stack 1 after merge: ";
    s1.printStack();

    cout << "Stack 2 after merge: ";
    s2.printStack(); // Should be empty

    return 0;
}
