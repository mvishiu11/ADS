/*Your goal is to write a program that will count the number of seats won by each party
in the elections. We have n parties and s seats, the parties are numbered with consecutive
numbers in [n] (starting from 1). The seats are distributed using the d’Hondt method.
The method works as follows. After all the votes have been counted, successive quotients
are calculated for each party. The party with the largest quotient wins one seat, and its
quotient is recalculated. This is repeated until the required number of seats is filled. The
formula for the quotient is
quot =
votes
seats + 1
where:
 votes is the total number of votes that party received,
 seats is the number of seats that party has been allocated so far, initially 0 for all
parties.
In the case of a tie, the seat goes to the party with the smallest number.
You should implement an algorithm that works in O((s + n) log n)-time.*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Party {
    int id;
    int votes;
    int seats;
    double quotient;

    bool operator<(const Party& other) const {
        if (quotient != other.quotient)
            return quotient < other.quotient;
        return id < other.id;
    }
};

class PartyHeap
{
    public:
    Party* heap;
    int size;
    int capacity;

    PartyHeap(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->heap = new Party[capacity];
    }

    int parent(int i) { return (i - 1) / 2; }

    void BuildHeap(Party* arr, int n) {
        size = n;
        heap = arr;

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(i);
    }

    void insert(Party party) {
        if (size == capacity) {
            cout << "Heap is full" << endl;
            return;
        }

        heap[size] = party;
        size++;

        int i = size - 1;
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify(int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if (l < size && heap[l].quotient < heap[largest].quotient)
        largest = l;

    if (r < size && heap[r].quotient < heap[largest].quotient)
        largest = r;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapify(largest);
    }
}

    Party extractMax() {
        if (size <= 0)
            return Party();

        if (size == 1) {
            size--;
            return heap[0];
        }

        Party root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);

        return root;
    }

    void print() {
        for (int i = 0; i < size; i++)
            cout << heap[i].id << " ";
        cout << endl;
    }
};

void printSeatsWon(Party* parties, int n, int s) {
    PartyHeap heap(n);
    heap.BuildHeap(parties, n);

    for (int i = 0; i < s; i++) {
        Party party = heap.extractMax();
        party.seats++;
        party.quotient = (double)party.votes / (party.seats + 1);
        heap.heap[0] = party; 
        heap.heapify(0);
    }

    for (int i = 0; i < n; i++)
        cout << heap.heap[i].seats << " ";
    cout << endl;
}

int main() {
    int ds = 0;
    cin >> ds;

    for(int i = 0; i < ds; i++)
    {
        int n = 0, s = 0;
        cin >> n >> s;

        Party* parties = new Party[n];
        for (int j = 0; j < n; j++) {
            parties[j].id = j + 1;
            cin >> parties[j].votes;
            parties[j].seats = 0;
            parties[j].quotient = (double)parties[j].votes;
        }

        printSeatsWon(parties, n, s);
        delete[] parties;
    }

    return 0;
}