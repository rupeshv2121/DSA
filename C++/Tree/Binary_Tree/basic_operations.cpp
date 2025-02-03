#include <iostream>
#include <limits.h>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    int rcount;
    int lcount;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->rcount = 0;
        this->lcount = 0;
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

    bool isPBT(int count)
    {
        count = count + 1;
        while (count % 2 == 0)
        {
            count = count / 2;
        }

        if (count == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Node *addNode2(Node *root, int data)
    {
        Node *newNode = new Node(data);
        if (root == NULL)
        {
            return newNode;
        }

        if (root->rcount == root->lcount)
        {
            root->left = addNode2(root->left, data);
            root->lcount += 1;
        }
        else if (root->rcount < root->lcount)
        {
            if (isPBT(root->lcount))
            {
                root->right = addNode2(root->right, data);
                root->rcount += 1;
            }
            else
            {
                root->left = addNode2(root->left, data);
                root->lcount += 1;
            }
        }
        return root;
    }

    // Search Function
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

        // Recursively search in left and right subtrees
        return search(root->left, data) || search(root->right, data);
    }

    // Pre-order Traversal
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

    // In-order Traversal
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

    // Post-order Traversal
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

        return max(leftHeight, rightHeight) + 1;
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
            return INT_MAX;
        }

        int leftMin = minNode(root->left);
        int rightMin = minNode(root->right);

        return min(root->data, min(leftMin, rightMin));
    }

    int maxNode(Node *root)
    {
        if (root == NULL)
        {
            return INT_MIN;
        }

        int leftMax = maxNode(root->left);
        int rightMax = maxNode(root->right);

        return max(root->data, max(rightMax, leftMax));
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

    Node *findDeepestNode(Node *root)
    {
        if (root == NULL)
            return NULL;
        if (!root->left && !root->right)
            return root;

        Node *left = findDeepestNode(root->left);
        Node *right = findDeepestNode(root->right);

        return right ? right : left;
    }

    Node *deleteDeepest(Node *root, Node *target)
    {
        if (root == NULL)
            return NULL;
        if (root == target)
            return NULL;

        if (root->left == target)
        {
            root->left = NULL;
            delete target;
        }
        else if (root->right == target)
        {
            root->right = NULL;
            delete target;
        }
        else
        {
            root->left = deleteDeepest(root->left, target);
            root->right = deleteDeepest(root->right, target);
        }
        return root;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (root == NULL)
        {
            return NULL;
        }

        if (root->data == key && root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        if (root->data == key)
        {
            Node *deepest = findDeepestNode(root);
            root->data = deepest->data;
            root = deleteDeepest(root, deepest);
            return root;
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);

        return root;
    }
};

int Binary_Tree::idx = -1;

void displayMenu()
{
    cout << "\n===== Binary Tree Menu =====\n";
    cout << "1. Add Nodes Using Array\n";
    cout << "2. Add Node Using Recursion\n";
    cout << "3. Pre-Order Traversal\n";
    cout << "4. In-Order Traversal\n";
    cout << "5. Post-Order Traversal\n";
    cout << "6. Search for a Node\n";
    cout << "7. Height of BT : \n";
    cout << "8. Sum Of Nodes of BT : \n";
    cout << "9. Min Node : \n";
    cout << "10. Max Node : \n";
    cout << "11. Count Node \n";
    cout << "12. Delete Node \n";
    cout << "14. Exit\n";
    cout << "============================\n";
    cout << "Enter your choice: ";
}

int main()
{
    Binary_Tree bt;
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
            int nodes[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
            bt.root = bt.addNode(nodes);
            cout << "Binary Tree created successfully" << endl;
            break;
        }

        case 2:
        {
            int a;
            cout << "Enter the number of nodes you want to add: ";
            int numNodes;
            cin >> numNodes;

            for (int i = 0; i < numNodes; i++)
            {
                cout << "Enter data for node " << i + 1 << ": ";
                cin >> a;
                bt.root = bt.addNode2(bt.root, a);
            }

            cout << "Binary Tree Created Successfully" << endl;
            break;
        }

        case 3:
        {
            cout << "Pre-Order Traversal: ";
            bt.preOrder(bt.root);
            cout << endl;
            break;
        }

        case 4:
        {
            cout << "In-Order Traversal: ";
            bt.inOrder(bt.root);
            cout << endl;
            break;
        }

        case 5:
        {
            cout << "Post-Order Traversal: ";
            bt.postOrder(bt.root);
            cout << endl;
            break;
        }

        case 6:
        {
            int searchData;
            cout << "Enter a value to search in the tree: ";
            cin >> searchData;

            if (bt.search(bt.root, searchData))
            {
                cout << "Data " << searchData << " is found in the tree." << endl;
            }
            else
            {
                cout << "Data " << searchData << " is not found in the tree." << endl;
            }
            break;
        }

        case 7:
        {
            cout << "Height of BT : " << bt.height(bt.root) << endl;
            break;
        }

        case 8:
        {
            cout << "Sum of Nodes : " << bt.sumNode(bt.root) << endl;
            break;
        }

        case 9:
        {
            cout << "Min Node : " << bt.minNode(bt.root);
            break;
        }

        case 10:
        {
            cout << "Max Node : " << bt.maxNode(bt.root);
            break;
        }

        case 11:
        {
            cout << "Total Nodes : " << bt.countNode(bt.root) << endl;
            break;
        }

        case 12:
        {
            bt.deleteNode(bt.root, 50);
            break;
        }
        case 14:
        {
            cout << "Existing the Operations of Binary Tree" << endl;
            break;
        }

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 14);

    return 0;
}
