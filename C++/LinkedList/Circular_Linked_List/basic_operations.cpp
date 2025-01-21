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

class CircularLL
{
    Node *head = NULL;
    Node *tail = NULL;

public:
    void addFirst(int data)
    {
        Node *newNode = new Node(data);
        if (head == NULL)
        {
            head = tail = newNode;
            newNode = head;
            return;
        }

        newNode->next = head;
        head = newNode;
        tail->next = head;
    }

    void addLast(int data)
    {
        Node *newNode = new Node(data);
        if (head == NULL)
        {
            head = tail = newNode;
            newNode->next = head;
            return;
        }

        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    }

    void addMiddle(int data, int idx)
    {
        Node *newNode = new Node(data);
        if (head == NULL)
        {
            head = tail = newNode;
            newNode->next = head;
            return;
        }

        int i = 0;
        Node *temp = head;
        do
        {
            temp = temp->next;
            i++;
        } while (i < idx - 1 && temp != head);

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void removeFirst()
    {
        if (head == NULL)
        {
            cout << "CLL is empty" << endl;
            return;
        }

        Node *remNode = head;
        head = head->next;
        tail->next = head;

        cout << "Removed First Node : " << remNode->data << endl;
        delete remNode;
    }

    void removeLast()
    {
        if (head == NULL)
        {
            cout << "CLL is empty" << endl;
            return;
        }

        Node *prev = head;
        do
        {
            prev = prev->next;
        } while (prev->next != tail);

        Node *remNode = tail;
        prev->next = head;
        tail = prev;

        cout << "Removed Last Node : " << remNode->data << endl;
        delete remNode;
    }

    void removeMiddle(int idx)
    {
        if (head == NULL)
        {
            cout << "CLL is empty" << endl;
            return;
        }

        int i = 0;
        Node *temp = head;
        Node *prev;

        do
        {
            prev = temp;
            temp = temp->next;
            i++;
        } while (i < idx - 1 && temp != head);

        Node *remNode = temp;
        prev->next = temp->next;
        cout << "Removed Node : " << remNode->data << endl;
        delete remNode;
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "CLL is empty" << endl;
            return;
        }
        Node *temp = head;
        do
        {
            cout << temp->data << "->";
            temp = temp->next;
        } while (temp != head);

        Node *curr = head;
        cout << curr->data << endl;
    }
};
int main()
{
    CircularLL cll;
    cll.addFirst(4);
    cll.addFirst(3);
    cll.addFirst(2);
    cll.addFirst(1);
    cll.addLast(5);
    cll.addLast(6);

    cll.addMiddle(7, 3);

    cll.removeFirst();
    cll.removeLast();
    cll.removeMiddle(3);

    cll.display();

    return 0;
}