#include <iostream>
#include <queue>
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
    int height(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return max(leftHeight, rightHeight) + 1; // in terms of Nodes
    }

    void printHeight(Node *root, int h)
    {
        if (root == NULL)
        {
            return;
        }

        if (h == 1)
        {
            cout << root->data << " ";
        }

        printHeight(root->left, h - 1);
        printHeight(root->right, h - 1);
    }

    // Recursion
    void levelOrder(Node *root)
    {
        int h = height(root);

        for (int i = 1; i <= h; i++)
        {
            printHeight(root, i);
        }
    }

    // Using Queue
    void levelOrder2(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        queue<Node *> q;
        q.push(root);
        q.push(NULL);

        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            if (curr == NULL)
            {
                cout << endl;
                if (q.empty())
                {
                    break;
                }
                else
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout << curr->data << " ";
                if (curr->left != NULL)
                {
                    q.push(curr->left);
                }

                if (curr->right != NULL)
                {
                    q.push(curr->right);
                }
            }
        }
    }

    int countNode(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        int leftCount = countNode(root->left);
        int rightCount = countNode(root->right);

        return leftCount + rightCount + 1;
    }

    int sumNode(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }

        int leftSum = sumNode(root->left);
        int rightSum = sumNode(root->right);

        return leftSum + rightSum + root->data;
    }

    int minNode(Node *root)
    {
        if (root == NULL)
        {
            return -1;
        }

        Node *temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }

        return temp->data;
    }

    int maxNode(Node *root)
    {
        if (root == NULL)
        {
            return -1;
        }

        Node *temp = root;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }

        return temp->data;
    }

    Node *emptyTree(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }

        root->left = emptyTree(root->left);
        root->right = emptyTree(root->right);

        cout << "Deleted Node : " << root->data << endl;
        delete root;

        return NULL;
    }

    Node *childNode(Node *root, int key)
    {
        if (root == NULL || root->left == NULL || root->right == NULL)
        {
            return NULL;
        }

        if (root->left && root->left->data == key)
        {
            return root->right;
        }
        if (root->right && root->right->data == key)
        {
            return root->left;
        }

        if (root->data < key)
        {
            return siblingNode(root->right, key);
        }
        else
        {
            return siblingNode(root->left, key);
        }
    }
};

void displayMenu()
{
    cout << "1. Add Node" << endl;
    cout << "2. delete Node" << endl;
    cout << "3. Search Node" << endl;
    cout << "4. Pre-Order" << endl;
    cout << "5. In-order" << endl;
    cout << "6. Post-Order" << endl;
    cout << "7. Level Order" << endl;
    cout << "8. Count Nodes" << endl;
    cout << "9. Sum Nodes" << endl;
    cout << "10. Min Node" << endl;
    cout << "11. Max Node" << endl;
    cout << "12. Empty Tree" << endl;
    cout << "13. childNode" << endl;
    // Under maintainence
    cout << "14. Height Of Tree" << endl;
}

int main()
{
    BST bst;
    int choice;

    do
    {
        displayMenu();
        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int nodes;
            cout << "Enter number of Node you want : ";
            cin >> nodes;
            int a;
            for (int i = 0; i < nodes; i++)
            {
                cout << "Enter data : ";
                cin >> a;
                bst.root = bst.addNode(bst.root, a);
            }

            break;
        }

        case 2:
        {
            int x;
            cout << "Enter The Data which you want to delete : ";
            cin >> x;
            bst.root = bst.deleteNode(bst.root, x);
            cout << "In-Order Traversal : ";
            bst.InOrder(bst.root);
            cout << endl;
            break;
        }

        case 3:
        {
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

            break;
        }

        case 4:
        {
            cout << "Pre-Order Traversal : ";
            bst.preOrder(bst.root);
            cout << endl;
            break;
        }

        case 5:
        {
            cout << "In-Order Traversal : ";
            bst.InOrder(bst.root);
            cout << endl;
            break;
        }

        case 6:
        {
            cout << "Post-Order Traversal : ";
            bst.postOrder(bst.root);
            cout << endl;
            break;
        }

        case 7:
        {
            bst.levelOrder(bst.root);
            cout << endl;
            break;
        }

        case 8:
        {
            cout << "Total Nodes in BST : " << bst.countNode(bst.root) << endl;
            break;
        }

        case 9:
        {
            cout << "Total Sum of Nodes : " << bst.sumNode(bst.root) << endl;
            break;
        }

        case 10:
        {
            cout << "Min Node : " << bst.minNode(bst.root) << endl;
            break;
        }
        case 11:
        {
            cout << "Max Node : " << bst.maxNode(bst.root) << endl;
            break;
        }

        case 12:
        {
            bst.emptyTree(bst.root);
            break;
        }

        case 13:
        {
            int y;
            cout << "Enter Sibling You want to find : ";
            cin >> y;

            Node *temp = bst.siblingNode(bst.root, y);
            cout << "Sibling Node : " << temp->data << endl;
            break;
        }

        case 14:
        {
            cout << "Height of BST : " << bst.height(bst.root) << endl;
            break;
        }

        default:
        {
            cout << "Invalid Input ! please try again" << endl;
        }
        }
    } while (choice != 14);

    // bst.levelOrder2(bst.root);

    return 0;
}