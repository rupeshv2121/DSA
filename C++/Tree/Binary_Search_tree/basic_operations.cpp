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
        }
        if (root->data < data)
        {
            root->right = addNode(root->right, data);
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

    Node *findInOrderSuccessor(Node *root)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }

        return root;
    }

    Node *deleteNode(Node *root, int data, bool isFirstCall = true)
    {
        if (root == NULL)
        {
            if (isFirstCall)
            {
                cout << "BST is Empty." << endl;
            }
            else
            {
                cout << "Data " << data << " not found in BST." << endl;
            }
            return NULL;
        }

        if (root->data < data)
        {
            root->right = deleteNode(root->right, data, false);
        }
        else if (root->data > data)
        {
            root->left = deleteNode(root->left, data, false);
        }
        else
        {
            // 0 child
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }
            // 1 child
            if (root->left == NULL)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == NULL)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            // 2 child
            Node *IS = findInOrderSuccessor(root->right);
            root->data = IS->data;
            root->right = deleteNode(root->right, IS->data, false);
        }
        return root;
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

    void InOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
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

int main()
{
    BST bst;
    int a;
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter data : ";
        cin >> a;
        bst.root = bst.addNode(bst.root, a);
    }

    cout << "Pre-Order Traversal : ";
    bst.preOrder(bst.root);
    cout << endl;

    cout << "In-Order Traversal : ";
    bst.InOrder(bst.root);
    cout << endl;

    cout << "Post-Order Traversal : ";
    bst.postOrder(bst.root);
    cout << endl;

    int b;
    cout << "Enter data you want to search : ";
    cin >> b;
    if (bst.search(bst.root, b))
    {
        cout << "Data Found" << endl;
    }
    else
    {
        cout << "Data Not Found" << endl;
    }

    bst.root = bst.deleteNode(bst.root, 5);
    cout << "In-Order Traversal : ";
    bst.InOrder(bst.root);
    cout << endl;

    return 0;
}