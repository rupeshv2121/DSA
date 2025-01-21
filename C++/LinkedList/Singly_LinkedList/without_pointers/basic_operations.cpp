#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data;
    int next;
    Node(int data)
    {
        this->data = data;
        this->next = -1;
    }
};

static int size;

class LinkedList
{
private:
    vector<Node> nodes;
    int headIdx;

public:
    LinkedList()
    {
        headIdx = -1;
    }

    void addFirst(int data)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);

        int newIdx = nodes.size() - 1;
        if (headIdx == -1)
        {
            headIdx = newIdx;
        }
        else
        {
            nodes[newIdx].next = headIdx;
            headIdx = newIdx;
        }
        }

    void addLast(int data)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        if (headIdx == -1)
        {
            headIdx = newIdx;
        }
        else
        {
            int currIdx = headIdx;
            while (nodes[currIdx].next != -1)
            {
                currIdx = nodes[currIdx].next;
            }

            nodes[currIdx].next = nodes.size() - 1;
        }
    }

    void addMiddle(int data, int idx)
    {
        Node newNode(data);
        size++;
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        if (headIdx == -1)
        {
            headIdx = newIdx;
            return;
        }

        if (idx == 0)
        {
            nodes[newIdx].next = headIdx;
            headIdx = newIdx;
            return;
        }

        int i = 0;
        int currIdx = headIdx;
        while (i < idx - 1 && nodes[currIdx].next != -1)
        {
            currIdx = nodes[currIdx].next;
            i++;
        }

        nodes[newIdx].next = nodes[currIdx].next;
        nodes[currIdx].next = newIdx;
    }
    void removeFirst()
    {
        if (headIdx == -1)
        {
            cout << "LL is empty";
        }

        int removeIdx = headIdx;
        headIdx = nodes[headIdx].next;
        size--;
        cout << "Removed First Node : " << nodes[removeIdx].data << endl;
    }

    void removeLast()
    {
        if (headIdx == -1)
        {
            cout << "LL is empty" << endl;
        }

        int prev;
        int currIdx = headIdx;
        while (nodes[currIdx].next != -1)
        {
            prev = currIdx;
            currIdx = nodes[currIdx].next;
        }

        cout << "Removed Last Node : " << nodes[currIdx].data << endl;
        size--;
        if (prev == -1)
        {
            headIdx = -1;
        }
        else
        {
            nodes[prev].next = -1;
        }
    }

    void removeMiddle(int idx)
    {
        if (headIdx == -1)
        {
            cout << "LL is empty";
            return;
        }

        // 1-> 2-> | 3 | -> 4-> 5-> -1
        int i = 0;
        int prev = -1;
        int currIdx = headIdx;
        while (i < idx && headIdx != -1)
        {
            i++;
            prev = currIdx;
            currIdx = nodes[currIdx].next;
        }

        cout << "Removed Middle Node : " << nodes[currIdx].data << endl;
        size--;
        nodes[prev].next = nodes[currIdx].next;
    }

    void reverse()
    {
        if (headIdx == -1)
        {
            cout << "LL is empty" << endl;
            return;
        }

        int prevIdx = -1;
        int currIdx = headIdx;
        int nextIdx;

        while (currIdx != -1)
        {
            nextIdx = nodes[currIdx].next;
            nodes[currIdx].next = prevIdx;
            prevIdx = currIdx;
            currIdx = nextIdx;
        }

        headIdx = prevIdx;
    }

    void display()
    {
        if (headIdx == -1)
        {
            cout << "LL is empty";
        }

        int currIdx = headIdx;
        while (currIdx != -1)
        {
            cout << nodes[currIdx].data << "->";
            currIdx = nodes[currIdx].next;
        }
        cout << "null" << endl;
    }
};

int main()
{
    LinkedList ll;
    ll.addFirst(4);
    ll.addFirst(2);
    ll.addLast(5);
    ll.addLast(6);
    ll.addFirst(1);
    ll.addMiddle(3, 2);
    // 1->2->3->4->5->6->null

    ll.display();
    ll.reverse();
    ll.display();

    ll.removeFirst();   // 1
    ll.removeLast();    // 6
    ll.removeMiddle(2); // 4

    cout << "LL Size : " << size << endl; // 3
    ll.display();                         // 2->3->5->null

    return 0;
}