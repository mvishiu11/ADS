#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Box
{
	public:
	
	int x;
	int y;
	int h;
	
	Box(int _x, int _y, int _h)
	{
		x = _x;
		y = _y;
		h = _h;
	}
	
	bool operator<=(const Box& b)
	{
		if (x <= b.x && y <= b.y)
			return true;
		if (x <= b.y && y <= b.x)
			return true;
		return false;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Box& b);
};

std::ostream& operator<<(std::ostream& stream, const Box& b)
{
	stream << b.x << "/" << b.y << "/" << b.h << "\n";
	return stream;
}

int getHighestTower(vector<Box>* boxes, vector<int>* highestTower)
{
    int n = (boxes->size());
	/* adding an element to the back of the vector pointed by highestTower */
	highestTower->push_back((*boxes)[0].h);

	int maxHeight = 0;

	for (int i = 1; i < n; i++) {							// O(n^2), basically LIS all over again
		highestTower->push_back((*boxes)[i].h);				// Set initial value to first value possible	
		for (int j = 0; j < i; j++) {						// For each box in range	
			if ((*boxes)[i] <= (*boxes)[j]) {				// If the box is smaller than the one before it
				(*highestTower)[i] = max(					// Set the height of the tower to the max of:
					(*highestTower)[i], 					// 1. The its current height
					((*highestTower)[j] + (*boxes)[i].h));  // 2. The height of the tower before it + the height of the box
			}
		}
	}

	for (int i = 0; i < n; i++) {							// O(n), find the max height by checking all heights
		if ((*highestTower)[i] > maxHeight) {
			maxHeight = (*highestTower)[i];
		}
	}

	return maxHeight;
}

void printBoxes( vector<Box> * boxes)
{
	cout << "\nBoxes:\n";
	for (int i =0; i < boxes -> size(); i++ )
	{
		cout << (*boxes)[i];
	}
}

int main()
{
	vector<Box> boxes; 
	vector<int> highestTower; 
	
	int z,n;
	cin >> z;
	while(z)
	{
		boxes.clear();
		highestTower.clear();
		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x,y,h;
			cin >> x >> y >> h;
			boxes.push_back( Box(x,y,h) );
		}
		cout << getHighestTower(&boxes, &highestTower) << "\n";
		z--;
		
	}
	return 1;
}