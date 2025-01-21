#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

static int size;

class DoublyLinkedList
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

        head->prev = newNode;
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
        newNode->prev = tail;
        tail = newNode;
    }

    void addMiddle(int data, int idx)
    {
        Node *newNode = new Node(data);
        size++;
        if (head == NULL)
        {
            head = tail = newNode;
        }

        int i = 0;
        Node *temp = head;
        while (i < idx - 1 && temp->next != NULL)
        {
            temp = temp->next;
            i++;
        }

        temp->next->prev = newNode;
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
    }

    void removeFirst()
    {
        if (head == NULL)
        {
            cout << "DLL is empty" << endl;
        }

        Node *remNode = head;
        head = head->next;
        head->prev = NULL;

        cout << "Removed First Node : " << remNode->data << endl;
        delete remNode;
    }

    void removeLast()
    {
        if (head == NULL)
        {
            cout << "DLL is empty" << endl;
            return;
        }

        Node *remNode = tail;
        tail->prev->next = NULL;
        cout << "Removed Last Node : " << remNode->data << endl;
        delete remNode;
    }

    void removeMiddle(int idx)
    {
        if (head == NULL)
        {
            cout << "DLL is empty" << endl;
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
        temp->next->prev = temp;
        temp->next = temp->next->next;

        cout << "Removed Node : " << remNode->data << endl;
        delete remNode;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "DLL is empty" << endl;
            return;
        }

        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "<->";
            temp = temp->next;
        }
        cout << "null" << endl;
    }
};

int main()
{
    DoublyLinkedList dll;
    dll.addFirst(4);
    dll.addFirst(3);
    dll.addFirst(2);
    dll.addFirst(1);

    dll.addLast(5);
    dll.addMiddle(6, 3);

    dll.removeFirst();
    dll.removeLast();
    dll.removeMiddle(1);

    dll.display();
    return 0;
}