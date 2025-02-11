#include <iostream>
using namespace std;

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(int arr[], int si, int mid, int ei)
{
    int n1 = mid - si + 1;
    int n2 = ei - mid;

    // Temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[si + i];

    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    // Merging process
    int i = 0, j = 0, k = si;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements (if any)
    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int si, int ei)
{
    if (si < ei)
    {
        int mid = si + (ei - si) / 2;
        mergeSort(arr, si, mid);
        mergeSort(arr, mid + 1, ei);
        merge(arr, si, mid, ei);
    }
}

int main()
{
    int arr[] = {5, 1, 3, 9, 2, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArr(arr, size);

    mergeSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    printArr(arr, size);

    return 0;
}
