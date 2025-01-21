#include <iostream>
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

static int size;

class LinkedList
{
    Node *head = NULL;
    Node *tail = NULL;

public:
    void addFirst(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (head == NULL)
        {
            head = tail = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }

    void addLast(int data)
    {
        Node *newNode = new Node(data);
        size++;
        if (head == NULL)
        {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        tail = newNode;
    }

    void addMiddle(int data, int idx)
    {
        Node *newNode = new Node(data);
        size++;
        if (head == NULL)
        {
            head = tail = newNode;
            return;
        }

        int i = 0;
        Node *temp = head;
        while (i < idx - 1 && temp->next != NULL)
        {
            temp = temp->next;
            i++;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void removeFirst()
    {
        if (head == NULL)
        {
            cout << "LL is empty" << endl;
        }

        Node *remNode = head;
        head = head->next;

        cout << "Removed First element : " << remNode->data << endl;
        delete remNode;
        size--;
    }

    void removeLast()
    {
        if (head == NULL)
        {
            cout << "LL is empty" << endl;
            return;
        }

        if (head->next == NULL)
        {
            cout << "Removed Last Node : " << head->data << endl;
            delete head;
            size--;
            head = tail = NULL;
            return;
        }

        Node *temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }

        Node *remNode = temp->next;
        tail = temp;
        tail->next = NULL;

        cout << "Removed Last Node : " << remNode->data << endl;
        delete remNode;
        size--;
    }

    void removeMiddle(int idx)
    {
        if (head == NULL)
        {
            cout << "LL is empty" << endl;
            return;
        }

        if (idx == 0)
        {
            cout << "Removed Node : " << head->data << endl;
            delete head;
            size--;
            head = tail = NULL;
            return;
        }

        int i = 0;
        Node *temp = head;
        while (i < idx - 1 && temp->next != NULL)
        {
            temp = temp->next;
            i++;
        }

        Node *remNode = temp->next;
        temp->next = temp->next->next;
        cout << "Removed Node : " << remNode->data << endl;

        delete remNode;
        size--;
    }

    void reverse()
    {
        if (head == NULL)
        {
            cout << "LL is empty" << endl;
            return;
        }

        Node *prev = NULL;
        Node *curr = head;
        Node *next;

        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "LL is empty" << endl;
        }
        Node *curr = head;
        while (curr != NULL)
        {
            cout << curr->data << "->";
            curr = curr->next;
        }

        cout << "null" << endl;
    }
};

int main()
{
    LinkedList ll;
    ll.addFirst(4);
    ll.addFirst(3);
    ll.addFirst(2);
    ll.addFirst(1);

    ll.addLast(5);
    ll.addMiddle(7, 3);
    cout << "Size : " << size << endl;

    ll.reverse();
    ll.display();

    ll.removeFirst();
    ll.removeLast();
    ll.removeMiddle(3);

    cout << "Size : " << size << endl;

    ll.display();
    return 0;
}