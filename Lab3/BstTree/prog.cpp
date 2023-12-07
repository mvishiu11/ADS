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

int BstTree::bstInsert(int _val)
{
    if (root == NULL)
    {
        root = new Node();
        root->val = _val;
        root->left = root->right = NULL;
        return 1;
    }

    Node *current = root;
    Node *parent = NULL;

    while (current != NULL)
    {
        if (_val == current->val)
        {
            return 0;
        }
        parent = current;

        if (_val < current->val)
            current = current->left;
        else
            current = current->right;
    }

    Node *newNode = new Node();
    newNode->val = _val;
    newNode->left = newNode->right = NULL;

    if (_val < parent->val)
        parent->left = newNode;
    else
        parent->right = newNode;

    return 1;
}

int BstTree::bstSearch(int _val)
{
    Node *current = root;

    while (current != NULL)
    {
        if (_val == current->val)
        {
            return 1;
        }
        else if (_val < current->val)
            current = current->left;
        else
            current = current->right;
    }

    return 0;
}

void BstTree::preOrderSeq()
{
    preOrder(root);
}

void BstTree::preOrder(Node *curr)
{
    if (curr != NULL)
    {
        cout << curr->val << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void BstTree::inOrderSeq()
{
    inOrder(root);
}

void BstTree::inOrder(Node *curr)
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

void BstTree::postOrder(Node *curr)
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
