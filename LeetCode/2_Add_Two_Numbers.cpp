#include <iostream>
#include <cmath>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class LinkedList
{

public:
    Node *head = NULL;
    void addFirst(int data)
    {
        Node *newNode = new Node(data);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
int addTwoNumber(Node *l1, Node *l2)
{
    Node *x = l1;
    Node *y = l2;

    int num = 0;
    int i = 0;
    while (x != NULL && y != NULL)
    {
        num = num + pow(10, i) * (x->data + y->data);
        x = x->next;
        y = y->next;
        i++;
    }
    return num + 1;
}

int main()
{
    LinkedList l1, l2;
    l1.addFirst(6);
    l1.addFirst(8);
    l1.addFirst(9);

    l2.addFirst(8);
    l2.addFirst(9);
    l2.addFirst(7);

    l1.display();
    l2.display();

    cout << addTwoNumber(l1.head, l2.head) << endl;

    return 0;
}