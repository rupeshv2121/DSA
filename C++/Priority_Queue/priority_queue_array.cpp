#include <iostream>
using namespace std;

class Item
{
public:
    int value, priority;
};

class Priority_Queue
{
    Item arr[100];
    int size;

public:
    Priority_Queue()
    {
        size = 0;
    }

    void enqueue(int value, int priority)
    {
        if (size < 100)
        {
            arr[size].value = value;
            arr[size].priority = priority;
            size++;
        }
        else
        {
            cout << "Queue is Full" << endl;
        }
    }

    void dequeue()
    {
        if (size == 0)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int highestPriorityIdx = 0;
        for (int i = 1; i < size; i++)
        {
            if (arr[i].priority > arr[highestPriorityIdx].priority)
            {
                highestPriorityIdx = i;
            }
        }

        cout << "Dequeued: " << arr[highestPriorityIdx].value << " (Priority: " << arr[highestPriorityIdx].priority << ")\n";

        for (int i = highestPriorityIdx; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    void display()
    {
        if (size == 0)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << "(" << arr[i].value << ", " << arr[i].priority << ") ";
        }
        cout << endl;
    }
};

int main()
{
    Priority_Queue pq;
    pq.enqueue(10, 2);
    pq.enqueue(20, 5);
    pq.enqueue(30, 1);
    pq.enqueue(40, 4);

    pq.display();

    pq.dequeue();
    pq.display();

    return 0;
}