#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

const int MAX = 4000;
int itemSize[MAX]; 
int itemValue[MAX];

//auxiliary function
void printTable(int ** A, int n, int W)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j=0; j<=W ; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************\n";
}

// function allocating memory for int table of size (n+1) x (W+1)
void allocate_memory_for_matrix(int** &A, int n, int W)
{
	A = new int* [n+1];
	for(int i=0; i<=n; i++)
	{
		A[i] = new int[W+1];
	}		
}

// function freeing memory taken by a table of size (n+1) x (W+1)
void free_memory_for_matrix(int** A, int n)
{
	for (int i=0;i<=n;i++)
	{
		delete [] A[i];
	}
	delete [] A;
}

int max(int a, int b) { return (a > b) ? a : b; }

void solve(int* s, int * v, int ** A, int n, int W) // s - sizes, v - values, A - table, n - number of items, W - knapsack capacity
{	// T(n) = O(n * W)
	for (int i = 0; i <= n; i++) {			// O(n), iterate over all rows
        for (int j = 0; j <= W; j++) { 		// O(W), iterate over all columns
            if (i == 0 || j == 0)			// Init first row and column with 0s
                A[i][j] = 0;			
            else if (s[i - 1] <= j)							    // If item fits in knapsack
                A[i][j] = max(									// Take the maximum of two cases: 								 
					v[i - 1] + A[i - 1][j - s[i - 1]],          // (1) nth item included 
					A[i - 1][j]);   					        // (2) nth item not included	
            else                                                // If item doesn't fit in knapsack
                A[i][j] = A[i - 1][j]; 							// Don't take it
        } 
    } 
}



int main()
{
	int z,n,W;
	cin >> z;
	while(z)
	{		
		cin >> n >> W;
		int ** tab;
		allocate_memory_for_matrix(tab,n,W);
		for(int i=0; i<n; i++)
		{
			cin >> itemSize[i];
		}
		for(int i=0; i<n; i++)
		{
			cin >> itemValue[i];
		}
		solve(itemSize,itemValue, tab, n, W);
		cout << tab[n][W] << "\n";
		free_memory_for_matrix(tab,n);
		z--;
	}
		
}
