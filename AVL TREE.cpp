#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int data = -9999, Node* left = NULL, Node* right = NULL, int height = 0)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->height = height;
    }
    
};
class AVL_Tree
{
public:
    Node* root;
    AVL_Tree(Node* root=NULL)
    {
        this->root = root;
    }
    bool isEmpty()
    {
        return (root == NULL);
    }
    bool isLeaf(Node* apex)
    {
        return (apex->left == NULL && apex->right == NULL);
    }
    int max(int i, int j)// return maximum number
    {
        if (i < j)
            return j;
        else
            return i;
    }
    int height(Node* apex)//calculate the height
    {
        if (apex == NULL)
            return  -1;
        if (isLeaf(apex))
            return 0;

        return 1 + max(height(apex->left), height(apex->right));
    }
    int getHeight(Node* apex)//gives the height
    {
        return (apex == NULL) ? -1 : apex->height;
    }
    int balancingFactor(Node* apex)//calculate the balancing-factor
    {
        return (apex==NULL)? 0: (getHeight(apex->left) - (getHeight(apex->right)));
    }
    bool isLeftShewed(Node* apex)//Left Heavy
    {
        return (balancingFactor(apex) > 1);
    }
    bool isRightShewed(Node* apex)//Right Heavy
    {
        return (balancingFactor(apex) < -1);
    }
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;                     //  x
        Node* temp = y->left;                   //    y                    
        y->left = x;                            //      z
        x->right = temp;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    Node* rightRotate(Node* x)
    {
        Node* y = x->left;                  //          x
        Node* temp = y->right;              //         Y
        y->right = x;                       //       z
        x->left = temp;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    Node* balance(Node* apex)
    {
        if (isLeftShewed(apex))
        {
            if (balancingFactor(apex->left) < 0)  // Left--Right Case
                apex->left = leftRotate(apex->left);
                
            return  rightRotate(apex);  // Left--Left case
        }
        if (isRightShewed(apex))
        {
            if (balancingFactor(apex->right) > 0)       // Right--Left Case
                apex->right = rightRotate(apex->right);
                
            return leftRotate(apex);    //Right--Right Case
        }
        return apex;
    }
    Node* insert(Node* apex, int val) //insert function through recursion
    {
        if (apex == NULL)
            return new Node(val);

        if (val < apex->data)
            apex->left = insert(apex->left, val);
        else
            apex->right = insert(apex->right, val);

        apex->height = max(getHeight(apex->left), getHeight(apex->right)) + 1;  //Height calculating
        
        
        return balance(apex);       //balancing check   
    }
    void insert(int val)//overloading
    {
        root = insert(root, val);
    }
  
    void nodeAtKDistance(Node* current, int k)
    {
        if (current == NULL)
            return;

        if (k == 0)
        {
            cout << current->data << "\t";
            return;
        }


        nodeAtKDistance(current->left, k - 1);
        nodeAtKDistance(current->right, k - 1);
    }
    void nodeAtKDistance(int k)//overloading
    {
        nodeAtKDistance(root, k);
    }
    void traverseLevelOrder()
    {
        cout << "\nLevel order travesal of the tree\n";
        int h = getHeight(root);
        for (int i = 0; i <= h; i++)
        {
            nodeAtKDistance(i);
            cout << endl;
        }
    }
    void traversPostOrder(Node* apex)
    {
        if (apex == NULL)
            return;
        traversPostOrder(apex->left);
        traversPostOrder(apex->right);
        cout << apex->data << "\t";
    }
    void traversePreOder(Node* apex)
    {
        if (apex == NULL)
            return;
        cout << apex->data << "\t";
        traversePreOder(apex->left);
        traversePreOder(apex->right);
    }
    void traverseInOrder(Node* apex)
    {
        if (apex == NULL)
            return;
        traverseInOrder(apex->left);
        cout << apex->data << "\t";
        traverseInOrder(apex->right);
    }
};

int main()
{
    AVL_Tree t1;
    t1.insert(14);
    t1.insert(4);
    t1.insert(15);
    t1.insert(3);
    t1.insert(9);
    t1.insert(18);
    t1.insert(7);
    t1.insert(16);
    t1.insert(20);
    t1.insert(5);
    t1.insert(17);
    
    t1.traverseInOrder(t1.root);
    t1.traverseLevelOrder();
    return 0;
}
