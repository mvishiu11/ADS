#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Party
{
    public:
	int number;
	int votes;
	double quotient;

	bool operator<(const Party& other) const
	{
		if (quotient == other.quotient)
		{
			return number > other.number;
		}
		return quotient < other.quotient;
	}
};

void heapify(vector<Party>& heap, int index)
{
	int l_child = 2 * index + 1, r_child = 2 * index + 2;

	if (l_child <= heap.size())
		heapify(heap, l_child);

	if (r_child <= heap.size())
		heapify(heap, r_child);

	if (l_child < heap.size())
	{
		if (heap[index] < heap[l_child])
		{
			swap(heap[index], heap[l_child]);
		}
	}

	if (r_child < heap.size())
	{
		if (heap[index] < heap[r_child])
		{
			swap(heap[index], heap[r_child]);
		}
	}
}

void allocate_seats(const vector<int>& votes, vector<int>& seats, int seat)
{
	vector<Party> heap;

	for (int i = 0; i < votes.size(); i++)
	{
		heap.push_back({ i,votes[i],(double)votes[i] });
	}

	while (seat--)
	{
		heapify(heap, 0);

		seats[heap[0].number] += 1;

		heap[0].quotient = (double)heap[0].votes / (seats[heap[0].number] + 1);
	}
}

void print_seats(const vector<int>& seats) {
    for (const auto& seat : seats) {
        cout << seat << " ";
    }
    cout << '\n';
}

int main() {
	int z, n, s;
	vector<int> votes, seats;
	cin >> z;
	while (z--)
	{
		votes.clear();
		seats.clear();

		cin >> n >> s;

		for (int i = 0; i < n; i++)
		{
			int val;

			cin >> val;

			votes.push_back(val);
			seats.push_back(0);
		}

		allocate_seats(votes, seats, s);

        print_seats(seats);
	}

	return 0;
}