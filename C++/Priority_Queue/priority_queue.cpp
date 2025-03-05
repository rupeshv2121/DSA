#include <iostream>
using namespace std;

class MaxHeap
{
    int *heap;
    int size;
    int capacity;

public:
    MaxHeap(int capacity)
    {
        this->capacity = capacity;
        heap = new int[capacity];
        size = 0;
    }

    int getParentIdx(int i)
    {
        return (i - 1) / 2;
    }

    int leftChildIdx(int i)
    {
        return 2 * i + 1;
    }

    int rightChildIdx(int i)
    {
        return 2 * i + 2;
    }

    void push(int value)
    {
        if (size == capacity)
        {
            cout << "Heap is full" << endl;
            return;
        }

        size++;
        int lastIdx = size - 1;
        heap[lastIdx] = value;

        while (lastIdx != 0 && heap[getParentIdx(lastIdx)] < heap[lastIdx])
        {
            swap(heap[lastIdx], heap[getParentIdx(lastIdx)]);
            lastIdx = getParentIdx(lastIdx);
        }
    }

    int top()
    {
        if (size == 0)
        {
            cout << "Heap is empty" << endl;
            return -1;
        }

        return heap[0];
    }

    void pop()
    {
        if (size == 0)
        {
            cout << "Heap is empty" << endl;
            return;
        }

        heap[0] = heap[size - 1];
        size--;
        heapify(0);
    }

    void heapify(int i)
    {
        int largest = i;
        int leftChild = leftChildIdx(i);
        int rightChild = rightChildIdx(i);

        if (leftChild < size && heap[leftChild] > heap[largest])
        {
            largest = leftChild;
        }

        if (rightChild < size && heap[rightChild] > heap[largest])
        {
            largest = rightChild;
        }

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    bool isEmpty()
    {
        if (size == 0)
        {
            return true;
        }
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    MaxHeap pq(10);

    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);

    cout << "Priority Queue: ";
    pq.display();

    cout << "Top element: " << pq.top() << endl;

    pq.pop();
    cout << "After pop, top element: " << pq.top() << endl;

    pq.display();

    return 0;
}