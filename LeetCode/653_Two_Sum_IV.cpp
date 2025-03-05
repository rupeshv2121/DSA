// #include <iostream>
// using namespace std;

// class Node
// {
// public:
//     int data;
//     Node *left;
//     Node *right;
//     Node(int data)
//     {
//         this->data = data;
//         this->left = NULL;
//         this->right = NULL;
//     }
// };

// class bst
// {
// public:
//     Node *root = NULL;

//     Node *addNode(Node *root, int data)
//     {
//         Node *newNode = new Node(data);
//         if (root == NULL)
//         {
//             return newNode;
//         }

//         if (root->data > data)
//         {
//             root->left = addNode(root->left, data);
//             return root;
//         }
//         else if (root->data < data)
//         {
//             root->right = addNode(root->right, data);
//             return root;
//         }

//         return root;
//     }

//     int countNode(Node *root, int count)
//     {
//         if (root == NULL)
//         {
//             return 0;
//         }

//         int leftCount = countNode(root->left, count + 1);
//         int rightCount = countNode(root->right, count + 1);

//         return leftCount + rightCount + 1;
//     }

//     void inOrder(Node *root, int arr[], int &i)
//     {
//         if (root == NULL)
//         {
//             return;
//         }

//         inOrder(root->left, arr, i);
//         arr[i++] = root->data;
//         inOrder(root->right, arr, i);
//     }
// };

// void printArr(int arr[], int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         cout << arr[i] << " ";
//     }
// }

// bool twoSum(int arr[], int size, int target)
// {
//     int i = 0, j = size - 1;

//     while (i < j)
//     {
//         int tempSum = arr[i] + arr[j];
//         if (tempSum == target)
//         {
//             return true;
//         }
//         else if (tempSum >= target)
//         {
//             j--;
//         }
//         else
//         {
//             i++;
//         }
//     }

//     return false;
// }

// int main()
// {
//     bst bst1;
//     int a;

//     for (int i = 0; i < 6; i++)
//     {
//         cout << "Enter data : ";
//         cin >> a;
//         bst1.root = bst1.addNode(bst1.root, a);
//     }

//     int count = bst1.countNode(bst1.root, 0);

//     int arr[count];

//     int i = 0;
//     bst1.inOrder(bst1.root, arr, i);
//     // printArr(arr, count);
//     cout << twoSum(arr, count, 28);

//     return 0;
// }

#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class BST
{
public:
    Node *root = NULL;

    Node *addNode(Node *root, int data)
    {
        Node *newNode = new Node(data);
        if (root == NULL)
        {
            return newNode;
        }

        if (root->data > data)
        {
            root->left = addNode(root->left, data);
            return root;
        }
        else if (root->data < data)
        {
            root->right = addNode(root->right, data);
            return root;
        }

        return root;
    }

    bool twoSum(Node *root, int k)
    {
        if (root == NULL)
        {
            return false;
        }

        Node *leftNode = root->left;
        Node *rightNode = root->right;

        if (leftNode && rightNode && (leftNode->data + rightNode->data == k))
        {
            return true;
        }

        twoSum(root->left, k);
        twoSum(root->right, k);

        return false;
    }
};

int main()
{
    BST bst;
    int a;

    for (int i = 0; i < 6; i++)
    {
        cout << "Enter data : ";
        cin >> a;
        bst.root = bst.addNode(bst.root, a);
    }

    cout << bst.twoSum(bst.root, 9);
}
