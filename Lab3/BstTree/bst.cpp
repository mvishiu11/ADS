#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int val;
};

class BstTree
{
public:
    Node *root;
    BstTree()
    {
        root = NULL;
    };
    void inOrderSeq();
    void postOrderSeq();
    void preOrderSeq();
    int bstInsert(int _val); // inserts _val to bstTree; returns 1 is _val is added (which may happen only when _val is not in bstTree) and 0 otherwise
    int bstSearch(int _val); // returns 1 if _val is in the bstTree and 0 otherwise
    ~BstTree();

private:
    void inOrder(Node *);
    void postOrder(Node *);
    void preOrder(Node *);
    void deleteNode(Node *);
};

BstTree::~BstTree()
{
    deleteNode(root);
}

void BstTree::deleteNode(Node *curr)
{
    if (curr != NULL)
    {
        deleteNode(curr->left);
        deleteNode(curr->right);
        delete curr;
    }
}

int BstTree::bstInsert(int _val)            // O(log n), where n is the number of nodes in the tree (thus log n is the height of the tree)
{
    if (root == NULL)					   // if the tree is empty
    {
        root = new Node();                 // set the root to the node we want to insert 
        root->val = _val;
        root->left = root->right = NULL;
        return 1;                        
    }

    Node *current = root;                  // otherwise, we start from the root
    Node *parent = NULL;				   // and we keep track of the parent of the current node, null for root

    while (current != NULL)				   // we traverse the tree until we find the right place to insert the node
    {
        if (_val == current->val)          // if the value is already in the tree, we don't insert it
        {
            return 0;
        }
        parent = current;                  // otherwise, we keep track of the parent of the current node

        if (_val < current->val)           // and we move to the left or right child of the current node, depending on the value we want to insert
            current = current->left;
        else
            current = current->right;
    }

    Node *newNode = new Node();			// when we find the right place, we create a new node
    newNode->val = _val;
    newNode->left = newNode->right = NULL;

    if (_val < parent->val)             // and we insert it as a child of the parent node
        parent->left = newNode;         // on the left if its value is smaller than parent value 
    else
        parent->right = newNode;        // or on the right otherwise

    return 1;
}

int BstTree::bstSearch(int _val)			// O(log n), where n is the number of nodes in the tree (thus log n is the height of the tree)
{
    Node *current = root;                   // we start from the root

    while (current != NULL)				    // and we traverse the tree until we find the value we are looking for (or end of the tree)
    {
        if (_val == current->val)		    // if we find it, we return 1
        {
            return 1;
        }
        else if (_val < current->val)	    // otherwise, we move to the left or right child of the current node, depending on the value we are looking for
            current = current->left;
        else
            current = current->right;
    }

    return 0;                               // if we didn't find it, return 0
}

void BstTree::preOrderSeq()
{
    preOrder(root);
}

void BstTree::preOrder(Node *curr)     // O(n), where n is the number of nodes in the tree
{
    if (curr != NULL)
    {
        cout << curr->val << " ";      // we print the value of the current node
        preOrder(curr->left);          // and then we recursively print the left and right subtrees
        preOrder(curr->right);
    }
}

void BstTree::inOrderSeq()
{
    inOrder(root);
}

void BstTree::inOrder(Node *curr)       // O(n), same thing as preOrder
{
    if (curr != NULL)
    {
        inOrder(curr->left);
        cout << curr->val << " ";
        inOrder(curr->right);
    }
}

void BstTree::postOrderSeq()
{
    postOrder(root);
}

void BstTree::postOrder(Node *curr)	    // O(n), same thing as preOrder
{
    if (curr != NULL)
    {
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->val << " ";
    }
}

int main()
{
    int z, n;
    string zstr, nstr;
    getline(cin, zstr);
    istringstream(zstr) >> z;
    while (z)
    {
        getline(cin, nstr);
        istringstream(nstr) >> n;
        BstTree bstTree = BstTree();
        for (int i = 0; i < n; i++)
        {
            string line;
            getline(cin, line);
            string instr;
            int num;
            istringstream(line) >> instr >> num;
            if (instr == "INSERT")
                cout << bstTree.bstInsert(num) << "\n";
            else if (instr == "SEARCH")
                cout << bstTree.bstSearch(num) << "\n";
            else if (instr == "PREORDER")
            {
                bstTree.preOrderSeq();
                cout << "\n";
            }
            else if (instr == "INORDER")
            {
                bstTree.inOrderSeq();
                cout << "\n";
            }
            else if (instr == "POSTORDER")
            {
                bstTree.postOrderSeq();
                cout << "\n";
            }
        }
        z--;
    }
}
