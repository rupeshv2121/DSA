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

class Binary_Tree
{
    static int idx;

public:
    Node *root = NULL;
    // Using Array
    Node *addNode(int nodes[])
    {
        idx++;
        if (nodes[idx] == -1)
        {
            return NULL;
        }

        Node *newNode = new Node(nodes[idx]);
        newNode->left = addNode(nodes);
        newNode->right = addNode(nodes);

        return newNode;
    }

    // Using Node
    Node *addNode2(Node *root, int data)
    {
        Node *newNode = new Node(data);
        if (root == NULL)
        {
            return newNode;
        }

        if (root->left == NULL)
        {
            root->left = newNode;
        }
        else if (root->right == NULL)
        {
            root->right = newNode;
        }
        else
        {
            root->left = addNode2(root->left, data);
        }

        return root;
    }

    bool search(Node *root, int data)
    {
        if (root == NULL)
        {
            return false;
        }

        if (root->data == data)
        {
            return true;
        }

        bool leftSubTree = search(root->left, data);
        if (leftSubTree)
        {
            return true;
        }

        bool rightSubTree = search(root->right, data);
        if (rightSubTree)
        {
            return true;
        }

        return false;
    }

    void preOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    void postOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
};

int Binary_Tree::idx = -1;

int main()
{
    // int nodes[] = {2, 6, -1, -1, 8, 9, -1, -1, 1, -1, -1};
    Binary_Tree bt;
    // Node *root = bt.addNode(nodes);

    // bt.preOrder(root);
    // cout << endl;
    // bt.inOrder(root);

    int a;
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter data : ";
        cin >> a;
        bt.root = bt.addNode2(bt.root, a);
    }

    cout << "Pre-Order Traversal : ";
    bt.preOrder(bt.root);
    cout << endl;

    cout << "In-Order Traversal : ";
    bt.inOrder(bt.root);
    cout << endl;

    cout << "Post-Order Traversal : ";
    bt.postOrder(bt.root);
    cout << endl;

    int b;
    cout << "Enter Data which you want to find : ";
    cin >> b;
    if (bt.search(bt.root, b))
    {
        cout << "Data Found" << endl;
    }
    else
    {
        cout << "Data Not Found" << endl;
    }

    return 0;
}