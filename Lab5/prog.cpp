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
		Node* root;
		BstTree()
		{
			root = NULL;
		};
		void inOrderSeq();
		void postOrderSeq();
		void preOrderSeq();
		int bstInsert(int _val); // inserts _val to bstTree; returns 1 is _val is added (which may happen only when _val is not in bstTree) and 0 otherwise
		int bstDelete(int _val); // deletes _val from bstTree; returns 1 if _val gets deleted and 0 otherwise
		int bstSearch(int _val); // returns 1 if _val is in the bstTree and 0 otherwise
		~BstTree();
	private:
		void inOrder(Node *);
		void postOrder(Node *);
		void preOrder(Node *);
		void deleteNode(Node*);
};

BstTree::~BstTree()
{
	deleteNode(root);
}

void BstTree::deleteNode(Node* curr)
{
	if (curr!=NULL)
	{
		deleteNode(curr->left);
		deleteNode(curr->right);
		delete curr;
	}
}

int BstTree::bstInsert(int _val)
{
	if (bstSearch(_val)) return 0; //if _val is in the tree

	Node* curr = new Node();
	curr->val = _val;
	curr->left = NULL;
	curr->right = NULL;
	if (root == NULL)
	{
		root = curr;
		return 1;
	}
	else
	{
		Node * prev = NULL;
		Node* temp = root;
		bool leftChild = false;
		while( temp != NULL)
		{
			if (_val <= temp->val)
			{
				prev = temp;
				temp = temp->left;
				leftChild = true;
			}
			else
			{
				prev = temp;
				temp = temp->right;
				leftChild = false;
			}
		}

		if (leftChild)
			prev -> left = curr;
		else
			prev -> right = curr;
		return 1;
	}
}


int BstTree::bstSearch(int _val)
{
	Node* curr = root;
	while(curr != NULL)
	{
		if (curr-> val == _val)
			return 1;
		if (_val < curr->val)
			curr = curr -> left;
		else
			curr = curr -> right;
	}
	return 0;
}


int BstTree::bstDelete(int _val)
{
    Node* curr = root;
    Node* parent = NULL;
    bool leftChild = false;

    // Search for the node to be deleted
    while (curr != NULL && curr->val != _val)
    {
        parent = curr;
        if (_val < curr->val)
        {
            curr = curr->left;
            leftChild = true;
        }
        else
        {
            curr = curr->right;
            leftChild = false;
        }
    }

    // If the value is not found, return 0
    if (curr == NULL)
        return 0;

    // Node with _val found, perform deletion
    if (curr->left == NULL && curr->right == NULL)
    {
        // Case 1: Node with no children
        if (parent == NULL)
            root = NULL; // Deleting the root
        else if (leftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
        delete curr;
    }
    else if (curr->left == NULL || curr->right == NULL)
    {
        // Case 2: Node with one child
        Node* child = (curr->left != NULL) ? curr->left : curr->right;
        if (parent == NULL)
            root = child; // Deleting the root
        else if (leftChild)
            parent->left = child;
        else
            parent->right = child;
        delete curr;
    }
    else
    {
        // Case 3: Node with two children
        Node* successorParent = curr;
        Node* successor = curr->right;

        // Find the smallest value in the right subtree
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // Swap values of current node and its successor
        curr->val = successor->val;

        // Delete the successor node (it has at most one child)
        if (successorParent->left == successor)
            successorParent->left = (successor->right != NULL) ? successor->right : NULL;
        else
            successorParent->right = (successor->right != NULL) ? successor->right : NULL;

        delete successor;
    }

    return 1;
}


void BstTree::preOrderSeq()
{
	preOrder(root);
}

void BstTree::preOrder(Node * curr)
{
	cout << curr->val << " ";
	if (curr->left != NULL)
		preOrder(curr->left);
	if (curr->right != NULL)
		preOrder(curr->right);
}

void BstTree::inOrderSeq()
{
	inOrder(root);
}

void BstTree::inOrder(Node * curr)
{
	if (curr->left != NULL)
		inOrder(curr->left);
	cout << curr->val <<" ";
	if (curr->right != NULL)
		inOrder(curr->right);
}

void BstTree::postOrderSeq()
{
	postOrder(root);
}

void BstTree::postOrder(Node * curr)
{
	if (curr->left != NULL)
		postOrder(curr->left);
	if (curr->right != NULL)
		postOrder(curr->right);
	cout << curr->val <<" ";
}


int main()
{
	int z,n;
	string zstr,nstr;
	getline(cin, zstr);
	istringstream(zstr) >> z;
	while(z)
	{
		getline(cin, nstr);
		istringstream(nstr) >> n;
		BstTree bstTree = BstTree();
		for (int i=0; i<n;i++)
		{
			string line;
			getline(cin, line);
			string instr;
			int num;
			istringstream(line) >> instr >> num;
			if (instr == "INSERT")
				cout << bstTree.bstInsert(num) << "\n";
			else if (instr == "SEARCH")
				cout << bstTree.bstSearch(num)<<"\n";
            else if (instr == "DELETE")
                cout << bstTree.bstDelete(num)<<"\n";
			else if (instr == "PREORDER")
			{
				bstTree.preOrderSeq();
				cout <<"\n";
			}
			else if (instr == "INORDER")
			{
				bstTree.inOrderSeq();
				cout <<"\n";
			}
			else if (instr == "POSTORDER")
			{
				bstTree.postOrderSeq();
				cout <<"\n";
			}
			else if (instr == "DELETE")
			{
				bstTree.bstDelete(num);
				cout <<"\n";
			}
		}
		z--;
	}
}
