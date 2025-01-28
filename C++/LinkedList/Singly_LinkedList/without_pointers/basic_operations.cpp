#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data;
    int next;
    Node(int data) : data(data), next(-1) {}
};

class LinkedList
{
private:
    vector<Node> nodes;
    int headIdx;
    int size;

public:
    LinkedList() : headIdx(-1), size(0) {}

    void addFirst(int data)
    {
        Node newNode(data);
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        size++;

        if (headIdx == -1)
        {
            headIdx = newIdx;
            return;
        }

        nodes[newIdx].next = headIdx;
        headIdx = newIdx;
    }

    void addLast(int data)
    {
        Node newNode(data);
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        size++;

        if (headIdx == -1)
        {
            headIdx = newIdx;
            return;
        }

        int currIdx = headIdx;
        while (nodes[currIdx].next != -1)
        {
            currIdx = nodes[currIdx].next;
        }

        nodes[currIdx].next = newIdx;
    }

    void addMiddle(int data, int idx)
    {
        if (idx < 0 || idx > size)
        {
            cout << "Invalid Index" << endl;
            return;
        }

        Node newNode(data);
        nodes.push_back(newNode);
        int newIdx = nodes.size() - 1;
        size++;

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
            return;
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
            return;
        }

        int prev = -1;
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
            return;
        }
        else
        {
            nodes[prev].next = -1;
            return;
        }
    }

    void removeMiddle(int idx)
    {
        if (idx < 0 || idx >= size)
        {
            cout << "Invalid index" << endl;
            return;
        }

        if (idx == 0)
        {
            removeFirst();
            return;
        }

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
            cout << "LL is empty" << endl;
            return;
        }

        int currIdx = headIdx;
        while (currIdx != -1)
        {
            cout << nodes[currIdx].data << "->";
            currIdx = nodes[currIdx].next;
        }
        cout << "null" << endl;
    }

    int getSize()
    {
        return size;
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
    // // 1->2->3->4->5->6->null

    // ll.display();
    // ll.reverse();
    // ll.display();

    ll.removeFirst();   // 1
    ll.removeLast();    // 6
    ll.removeMiddle(0); // 5

    cout << "LL Size : " << ll.getSize() << endl; // 3
    ll.display();                                 // 5->4->3->2->null

    return 0;
}

// #include <iostream>
// using namespace std;

// class LinkedList
// {
// private:
//     int arr[100];
//     int next[100];
//     int head;
//     int size;

// public:
//     LinkedList()
//     {
//         head = -1;
//         size = 0;
//     }
//     void addFirst(int value)
//     {
//         arr[size] = value;
//         next[size] = head;
//         head = size;
//         size++;
//     }
//     void addLast(int value)
//     {
//         arr[size] = value;
//         next[size] = -1;

//         if (head == -1)
//         {
//             head = size;
//         }
//         else
//         {
//             int current = head;
//             while (next[current] != -1)
//             {
//                 current = next[current];
//             }
//             next[current] = size;
//         }
//         size++;
//     }

//     void addMiddle(int data, int idx)
//     {
//         arr[size] = data;
//         int newIdx = size;
//         size++;

//         int i = 0;

//         int prev;
//         int curr = head;
//         while (i < idx)
//         {
//             prev = curr;
//             curr = next[curr];
//             i++;
//         }

//         next[newIdx] = curr;
//         next[prev] = newIdx;
//     }

//     void removeFirst()
//     {
//         int remVal = arr[head];
//         head = next[head];
//         cout << "Removed First Node : " << remVal << endl;
//     }

//     void removeLast()
//     {
//         int prev;
//         int curr = head;
//         while (next[curr] != -1)
//         {
//             prev = curr;
//             curr = next[curr];
//         }
//         int remVal = arr[curr];
//         next[prev] = -1;
//         cout << "Removed Last Node : " << remVal << endl;
//     }

//     void removeMiddle(int idx)
//     {
//         int i = 0;
//         int curr = head;
//         while (i < idx - 1)
//         {
//             curr = next[curr];
//             i++;
//         }

//         int remVal = arr[next[curr]];
//         next[curr] = next[next[curr]];
//         cout << "Removed Node:  " << remVal << endl;
//     }
//     void display()
//     {
//         if (head == -1)
//         {
//             cout << "List is empty." << endl;
//             return;
//         }

//         int current = head;
//         while (current != -1)
//         {
//             cout << arr[current] << " -> ";
//             current = next[current];
//         }
//         cout << "null" << endl;
//     }
// };

// int main()
// {
//     LinkedList list;

//     list.addFirst(10);
//     list.addFirst(20);
//     list.addFirst(30);
//     list.addFirst(40);
//     list.addFirst(50);
//     list.display();

//     list.addMiddle(8, 3);

//     // list.removeFirst();
//     // list.removeLast();
//     list.removeMiddle(2);

//     list.display();

//     return 0;
// }
