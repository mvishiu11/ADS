#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Node
{
	public:
		Node *left;
		Node *right;
		int val;
};


class BinaryTree
{
	public:
		Node* root;
		BinaryTree()
		{
			root = NULL;
		};
		BinaryTree(string fO, string sO, vector<int>* firstOrder, vector<int>* secondOrder, int n);
		void inOrderSeq();	
		void postOrderSeq();
		void preOrderSeq();
		~BinaryTree();
	private:
		void inOrder(Node *);
		void postOrder(Node *);
		void preOrder(Node *);
		void deleteNode(Node*);
		Node* prein(vector<int>* firstOrder, vector<int>* secondOrder, int preOrderL, int inOrderL, int size);
		Node* inpost(vector<int>* firstOrder, vector<int>* secondOrder, int inOrderL, int postOrderL, int size);
		Node* prepost(vector<int>* preOrder, vector<int>* postOrder, int preOrderL, int postOrderL, int size);
};

BinaryTree::~BinaryTree()
{
	deleteNode(root);
}

void BinaryTree::deleteNode(Node* curr)
{
	if (curr!=NULL)
	{
		deleteNode(curr->left);
		deleteNode(curr->right);
		//cout << "Usuwanie noda z kluczem:" << curr ->val << "\n" ;
		delete curr;
	}
}


BinaryTree::BinaryTree(string firstOrderName, string secondOrderName, vector<int>* firstOrder, vector<int>* secondOrder, int n)
{
	if ((firstOrderName=="PREORDER") && (secondOrderName=="INORDER"))
	{
		root = prein(firstOrder, secondOrder,0,0,n);
		return;
	}
	if ((firstOrderName=="INORDER") && (secondOrderName=="POSTORDER"))
	{
		root = inpost(firstOrder, secondOrder,0,0,n);
		return;
	}
	if ((firstOrderName=="PREORDER") && (secondOrderName=="POSTORDER"))
	{
		root = prepost(firstOrder, secondOrder,0,0,n);
		return;
	}
}

Node* BinaryTree::prepost(vector<int>* preOrder, vector<int>* postOrder, int preOrderL, int postOrderL, int size)
{
    if (size == 0)
        return NULL;

    Node* root = new Node();
    root->val = (*preOrder)[preOrderL];

    if (size == 1)
        return root;

    int i;
    for (i = 0; i < size; i++) {
        if (((*postOrder)[postOrderL + i] == (*preOrder)[preOrderL + 1]) && ((*postOrder)[postOrderL + i] != 0 && (*preOrder)[preOrderL + 1] != 0))
            break;
    }

    root->left = prepost(preOrder, postOrder, preOrderL + 1, postOrderL, i + 1);
    root->right = prepost(preOrder, postOrder, preOrderL + i + 2, postOrderL + i + 1, size - i - 2);

    return root;
}

Node* BinaryTree::prein(vector<int>* preOrder, vector<int>* inOrder, int preOrderL, int inOrderL, int size)
{
    if (size == 0)
        return NULL;

    Node* root = new Node();
    root->val = (*preOrder)[preOrderL];

    if (size == 1)
        return root;

    int i;
    for (i = 0; i < size; i++) {
        if (((*inOrder)[inOrderL + i] == (*preOrder)[preOrderL]) && ((*inOrder)[inOrderL + i] != 0 && (*preOrder)[preOrderL] != 0))
            break;
    }

    root->left = prein(preOrder, inOrder, preOrderL + 1, inOrderL, i);
    root->right = prein(preOrder, inOrder, preOrderL + i + 1, inOrderL + i + 1, size - i - 1);

    return root;
}

Node* BinaryTree::inpost(vector<int>* inOrder, vector<int>* postOrder, int inOrderL, int postOrderL, int size)
{
    if (size == 0)
        return NULL;

    Node* root = new Node();
    root->val = (*postOrder)[postOrderL + size - 1];

    if (size == 1)
        return root;

    int i;
    for (i = 0; i < size; i++) {
        if (((*inOrder)[inOrderL + i] == root->val) && (*inOrder)[inOrderL + i] != 0)
            break;
    }

    root->left = inpost(inOrder, postOrder, inOrderL, postOrderL, i);
    root->right = inpost(inOrder, postOrder, inOrderL + i + 1, postOrderL + i, size - i - 1);

    return root;
}

void BinaryTree::preOrderSeq()
{
	preOrder(root);
}

void BinaryTree::preOrder(Node * curr)
{
	if (curr == NULL) 
	{
		cout <<"0 ";
		return;
	}
	cout << curr->val <<" ";
	preOrder(curr->left);
	preOrder(curr->right);
}

void BinaryTree::inOrderSeq()
{
	inOrder(root);
}

void BinaryTree::inOrder(Node * curr)
{
	if (curr == NULL) 
	{
		cout << "0 ";
		return;
	}
	inOrder(curr->left);
	cout << curr->val <<" ";
	inOrder(curr->right);
}

void BinaryTree::postOrderSeq()
{
	postOrder(root);
}

void BinaryTree::postOrder(Node * curr)
{
	if (curr == NULL) 
	{
		cout << "0 ";
		return;
	}
	postOrder(curr->left);
	postOrder(curr->right);
	cout << curr->val <<" ";
}

int main()
{
	vector<int> firstOrder; 
	vector<int> secondOrder; 
	int z;
	string line;
	getline(cin, line);
	istringstream(line) >> z;
	while(z)
	{
		getline(cin, line);
		string firstOrderName,secondOrderName;
		int n;
		istringstream(line) >> firstOrderName >> secondOrderName >> n;
		firstOrder.clear();
		secondOrder.clear();
		getline(cin, line);
		istringstream firstString(line);
		getline(cin, line);
		istringstream secondString(line);
		for(int i =0; i<n; i++)
		{
			int val;
			firstString >> val;
			firstOrder.push_back(val);
			secondString >> val;
			secondOrder.push_back(val);
		}
		
		BinaryTree binTree = BinaryTree(firstOrderName, secondOrderName, &firstOrder, &secondOrder, n);	
		//cout << firstOrderName << " " << secondOrderName <<"\n";

		if ((firstOrderName == "PREORDER") && (secondOrderName == "INORDER"))
		{
			binTree.postOrderSeq();
			cout << "\n";
		} else
		if ((firstOrderName == "INORDER") && (secondOrderName == "POSTORDER"))
		{
			binTree.preOrderSeq();
			cout << "\n";
		} else
		if ((firstOrderName == "PREORDER") && (secondOrderName == "POSTORDER"))
		{
			binTree.inOrderSeq();
			cout << "\n";			
		}
		z--;
	}
}




