#include <iostream>
using namespace std;

class QueueNode
{
public:
    int data;
    QueueNode *next;

    QueueNode(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
class Queue
{
    QueueNode *frontNode;
    QueueNode *rearNode;

public:
    Queue() : frontNode(NULL), rearNode(NULL) {}
    bool isEmpty()
    {
        return frontNode == NULL;
    }

    void enQueue(int data)
    {
        QueueNode *newQueueNode = new QueueNode(data);
        if (rearNode == NULL)
        {
            frontNode = rearNode = newQueueNode;
            return;
        }

        rearNode->next = newQueueNode;
        rearNode = newQueueNode;
    }

    void deQueue()
    {
        if (isEmpty())
        {
            return;
        }

        QueueNode *temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == NULL)
        {
            rearNode = NULL;
        }
        delete temp;
    }

    int front()
    {
        if (!isEmpty())
        {
            return frontNode->data;
        }

        return -1;
    }

    void display()
    {
        QueueNode *temp = frontNode;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

int main()
{
    Queue q;
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.deQueue();

    q.display();
    cout << endl;
    cout << q.front();
    return 0;
}