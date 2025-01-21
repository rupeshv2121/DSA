#include <iostream>
using namespace std;
#include <vector>

class Node
{
public:
    int data;
    int next;
    int prev;
    Node(int data)
    {
        this->data = data;
        this->next = -1;
        this->prev = -1;
    }
};

static int size;

class DoublyLinkedList
{
    vector<Node> nodes;
    int headIdx;
    int tailIdx;

public:
    DoublyLinkedList()
    {
        headIdx = -1;
        tailIdx = -1;
    }

    void addFirst(int data)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        if (headIdx == -1)
        {
            headIdx = tailIdx = newIdx;
            return;
        }

        nodes[headIdx].prev = newIdx;
        nodes[newIdx].next = headIdx;
        headIdx = newIdx;
    }

    void addLast(int data)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;

        if (headIdx == -1)
        {
            headIdx = tailIdx = newIdx;
            return;
        }

        nodes[newIdx].prev = tailIdx;
        nodes[tailIdx].next = newIdx;
        tailIdx = newIdx;
    }

    void addMiddle(int data, int idx)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;

        if (headIdx == -1)
        {
            headIdx = tailIdx = newIdx;
            return;
        }

        int i = 0;
        int currIdx = headIdx;
        while (i < idx - 1 && nodes[currIdx].next != -1)
        {
            i++;
            currIdx = nodes[currIdx].next;
        }

        nodes[newIdx].next = nodes[currIdx].next;
        nodes[newIdx].prev = currIdx;
        nodes[currIdx].next = newIdx;
    }

    void removeFirst()
    {
        if (headIdx == -1)
        {
            cout << "DLL is empty" << endl;
        }

        int removeIdx = headIdx;
        headIdx = nodes[headIdx].next;
        nodes[headIdx].prev = -1;

        cout << "Removed First Node : " << nodes[removeIdx].data << endl;
        size--;
    }

    void removeLast()
    {
        if (headIdx == -1)
        {
            cout << "DLL is empty" << endl;
        }

        if (headIdx == tailIdx)
        {
            headIdx = -1;
            tailIdx = -1;
        }
        else
        {
            cout << "Removed Last Node : " << nodes[tailIdx].data << endl;
            size--;
            tailIdx = nodes[tailIdx].prev;
            nodes[tailIdx].next = -1;
        }
    }

    void removeMiddle(int idx)
    {
        if (headIdx == -1)
        {
            cout << "DLL is empty" << endl;
            return;
        }

        if (headIdx == tailIdx)
        {
            cout << nodes[headIdx].data << endl;
            size--;
            headIdx = -1;
            tailIdx = -1;
            return;
        }

        if (idx == 0)
        {
            size--;
            removeFirst();
        }

        int i = 0;
        int prev = -1;
        int currIdx = headIdx;
        while (i < idx && currIdx != -1)
        {
            i++;
            prev = currIdx;
            currIdx = nodes[currIdx].next;
        }

        if (currIdx == -1)
        {
            cout << "Index out of bounds" << endl;
            return;
        }

        cout << "Removed Middle Node : " << nodes[currIdx].data << endl;
        size--;
        if (currIdx == tailIdx)
        {
            size--;
            removeLast();
        }

        nodes[prev].next = nodes[currIdx].next;
        nodes[nodes[currIdx].next].prev = prev;
    }
    void display()
    {
        if (headIdx == -1)
        {
            cout << "DLL is empty";
        }
        int currIdx = headIdx;
        while (currIdx != -1)
        {
            cout << nodes[currIdx].data << " <-> ";
            currIdx = nodes[currIdx].next;
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
    dll.addLast(6);

    dll.addMiddle(7, 3);

    cout << "Size : " << size << endl;

    dll.removeFirst();
    dll.removeLast();
    dll.removeMiddle(2);

    dll.display();
    cout << "Size : " << size << endl;
    return 0;
}