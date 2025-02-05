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

class QueueNode
{
public:
    Node *data;
    QueueNode *next;

    QueueNode(Node *data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Queue
{
    QueueNode *front;
    QueueNode *rear;

public:
    Queue() : front(NULL), rear(NULL) {}
    void enQueue(Node *data)
    {
        QueueNode *newQueueNode = new QueueNode(data);
        if (rear == NULL)
        {
            front = rear = newQueueNode;
            return;
        }

        rear->next = newQueueNode;
        rear = newQueueNode;
    }

    Node *deQueue()
    {
        if (front == NULL)
        {
            cout << "Queue is empty" << endl;
            return NULL;
        }

        QueueNode *temp = front;
        Node *currTemp = temp->data;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
        return currTemp;
    }

    Node *getTop()
    {
        return front ? front->data : NULL;
    }

    bool isEmpty()
    {
        return front == NULL;
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

    // using recursion
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

    // using queue
    Node *addNode3(Node *root, int data)
    {
        Node *newNode = new Node(data);
        if (root == NULL)
        {
            return newNode;
        }

        Queue q;
        q.enQueue(root);

        while (!q.isEmpty())
        {
            Node *currNode = q.getTop();
            q.deQueue();
            if (currNode->left == NULL)
            {
                currNode->left = newNode;
                return root;
            }
            else
            {
                q.enQueue(currNode->left);
            }

            if (currNode->right == NULL)
            {
                currNode->right = newNode;
                return root;
            }
            else
            {
                q.enQueue(currNode->right);
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
        Queue q;
        q.enQueue(root);
        Node *deepest = NULL;

        while (!q.isEmpty())
        {
            deepest = q.getTop();
            q.deQueue();

            if (deepest->left)
                q.enQueue(deepest->left);
            if (deepest->right)
                q.enQueue(deepest->right);
        }

        return deepest;
    }

    // Function to delete the deepest node
    void deleteDeepest(Node *root, Node *deepest)
    {
        Queue q;
        q.enQueue(root);

        while (!q.isEmpty())
        {
            Node *temp = q.getTop();
            q.deQueue();

            if (temp->left)
            {
                if (temp->left == deepest)
                {
                    temp->left = NULL;
                    delete deepest;
                    return;
                }
                else
                {
                    q.enQueue(temp->left);
                }
            }

            if (temp->right)
            {
                if (temp->right == deepest)
                {
                    temp->right = NULL;
                    delete deepest;
                    return;
                }
                else
                {
                    q.enQueue(temp->right);
                }
            }
        }
    }

    // Function to delete a node with a given key
    Node *deleteNode(Node *root, int key)
    {
        if (root == NULL)
            return NULL;

        if (root->left == NULL && root->right == NULL)
        {
            if (root->data == key)
            {
                delete root;
                return NULL;
            }
            else
            {
                return root;
            }
        }

        Queue q;
        q.enQueue(root);
        Node *keyNode = NULL, *temp = NULL;

        // Level-order traversal to find the node to be deleted and the last node
        while (!q.isEmpty())
        {
            temp = q.getTop();
            q.deQueue();

            if (temp->data == key)
                keyNode = temp;

            if (temp->left)
                q.enQueue(temp->left);

            if (temp->right)
                q.enQueue(temp->right);
        }

        // If the node to delete is found
        if (keyNode)
        {
            Node *deepest = findDeepestNode(root);
            keyNode->data = deepest->data;
            deleteDeepest(root, deepest);
        }

        return root;
    }
};

int Binary_Tree::idx = -1;

void displayMenu()
{
    cout << "\n===== Binary Tree Menu =====\n";
    cout << "1. Add Nodes Using Array\n";
    cout << "2. Add Node Using Recursion\n";
    cout << "3. Add Node using queue\n";
    cout << "4. Pre-Order Traversal\n";
    cout << "5. In-Order Traversal\n";
    cout << "6. Post-Order Traversal\n";
    cout << "7. Search for a Node\n";
    cout << "8. Height of BT : \n";
    cout << "9. Sum Of Nodes of BT : \n";
    cout << "10. Min Node : \n";
    cout << "11. Max Node : \n";
    cout << "12. Count Node \n";
    cout << "13. Delete Node \n";
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
            int a;
            for (int i = 0; i < 7; i++)
            {
                cout << "Enter data : ";
                cin >> a;
                bt.root = bt.addNode3(bt.root, a);
            }
            break;
        }

        case 4:
        {
            cout << "Pre-Order Traversal: ";
            bt.preOrder(bt.root);
            cout << endl;
            break;
        }

        case 5:
        {
            cout << "In-Order Traversal: ";
            bt.inOrder(bt.root);
            cout << endl;
            break;
        }

        case 6:
        {
            cout << "Post-Order Traversal: ";
            bt.postOrder(bt.root);
            cout << endl;
            break;
        }

        case 7:
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

        case 8:
        {
            cout << "Height of BT : " << bt.height(bt.root) << endl;
            break;
        }

        case 9:
        {
            cout << "Sum of Nodes : " << bt.sumNode(bt.root) << endl;
            break;
        }

        case 10:
        {
            cout << "Min Node : " << bt.minNode(bt.root);
            break;
        }

        case 11:
        {
            cout << "Max Node : " << bt.maxNode(bt.root);
            break;
        }

        case 12:
        {
            cout << "Total Nodes : " << bt.countNode(bt.root) << endl;
            break;
        }

        case 13:
        {
            int key;
            cout << "Enter the node value to delete: ";
            cin >> key;
            bt.root = bt.deleteNode(bt.root, key);

            cout << "In-Order Traversal after Deletion: ";
            bt.inOrder(bt.root);
            cout << endl;

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
