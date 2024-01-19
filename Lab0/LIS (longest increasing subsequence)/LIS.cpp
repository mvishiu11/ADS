#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

const int MAX = 4000000;
int tab[MAX];
int lis[MAX];
int glob;


void printTable(int * t, int n)
{
	for (int i=0; i<n; i++)
	{
		cout << t[i] << " ";
	}
	cout << endl;
}


void computeLIS(int * t, int * lis, int n) // T(n) = O(n^2)
{
	lis[0] = 1;
	for (int i = 1; i < n; i++) {		   // O(n) iterations, iterate over all elements of t
		lis[i] = 1;						   // Set initial value to min, ergo 1 in this case	
		for (int j = 0; j < i; j++)						// O(n)	iterations in the worst case (for the last iter), iterate over elements of t smaller than i
			if (t[i] > t[j] && lis[i] < lis[j] + 1)		// O(1) comparison, if num at t[i] is bigger than that at t[j] and its LIS is smaller, rectify that
				lis[i] = lis[j] + 1;
	}
}


int main()
{
	int z,n;
	cin >> z;
	while(z)
	{
		cin >> n;
		for(int i=0; i<n; i++)
		{
			cin >> tab[i];
		}
		//printTable(tab,n);
		computeLIS(tab,lis,n);
		printTable(lis,n);
		z--;
	}
		
}
