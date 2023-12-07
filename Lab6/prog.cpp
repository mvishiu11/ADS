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

struct CompareQuotient {
    bool operator()(const Party& a, const Party& b) {
        return a.quotient < b.quotient;
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
        if (l < size && heap[l] < heap[largest])
            largest = l;
        if (r < size && heap[r] < heap[largest])
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
        for (int i = 0; i < size; ++i) {
            cout << heap[i].id << " ";
        }
        cout << endl;
    } 
};

void distributeSeats(Party* parties, int totalSeats) {
    PartyHeap* maxHeap = new PartyHeap(totalSeats);
    maxHeap->BuildHeap(parties, totalSeats);

    for (int i = 0; i < totalSeats; ++i) {
        Party party = maxHeap->extractMax();
        
        party.seats++;
        party.quotient = static_cast<double>(party.votes) / (party.seats + 1);

        maxHeap->insert(party);
        maxHeap->print();
    }
    delete maxHeap;
}

int main() {
    int datasets;
    cin >> datasets;

    while (datasets--) {
        int numParties, numSeats;
        cin >> numParties >> numSeats;

        Party* parties = new Party[numParties];

        for (int i = 0; i < numParties; ++i) {
            parties[i].id = i + 1;
            cin >> parties[i].votes;
            parties[i].seats = 0;
            parties[i].quotient = static_cast<double>(parties[i].votes) / (parties[i].seats + 1);
        }

        distributeSeats(parties, numSeats);

        for (int i = 0; i < numParties; ++i) {
            cout << parties[i].seats << " ";
        }
        cout << endl;
    }

    return 0;
}