// https://github.com/PacktPublishing/CPP-Data-Structures-and-Algorithms/blob/master/Chapter07/Binary_Heap/src/BinaryHeap.cpp

#include <iostream>
#include <vector>
using namespace std;


class BinaryHeap {
private:
  vector<int> vect;
  int heapSize;

  int p(int i) { return i >> 1; }  // i//2
  int l(int i) { return i << 1; }  // i*2
  int r(int i) { return (i << 1)+1; }  // i*2+1

  void ShiftUp(int index) {
    if(index == 1) return;  // root
    if(vect[index] > vect[p(index)]) {
      swap(vect[index], vect[p(index)]);
      ShiftUp(p(index));
    }
  }
  void ShiftDown(int i) {
    if(i > heapSize) return;

    int swapId = i;
    if(l(i) <= heapSize && vect[i] < vect[l(i)])
      swapId = l(i);
    else if(r(i) <= heapSize && vect[i] < vect[r(i)])
      swapId = r(i);
    if(swapId != i) {
      swap(vect[i], vect[swapId]);
      ShiftDown(swapId);
    }
  }

public:
  BinaryHeap() {
    vect.clear();
    vect.push_back(-1);  // dummy value -1 in index [0]
    heapSize = 0;
  }

  bool IsEmpty() { return heapSize == 0; }

  void Insert(int key) {
    if(heapSize + 1 >= (int)vect.size())  // initial: heapSize = 0, vect.size() = 1
      vect.push_back(0);
    vect[++heapSize] = key;
    ShiftUp(heapSize);
  }

  int ExtractMax() {
    int maxVal = vect[1];
    swap(vect[1], vect[heapSize--]);  // vect[heapSize] is inactivate
    ShiftDown(1);
    return maxVal;
  }

  int GetMax() {
    return vect[1];
  }
};


int main()
{
    cout << "Priority Queue" << endl;

    // Instantiate priority queue
    BinaryHeap * priorityQueue = new BinaryHeap();

    // Check if the queue is empty
    // it should be TRUE
    cout << "Is queue empty? ";
    if(priorityQueue->IsEmpty())
        cout << "TRUE";
    else
        cout << "FALSE";
    cout << endl;

    // Insert a new element
    priorityQueue->Insert(14);
    cout << "Insert 14 to queue" << endl;

    // Check again if the queue is empty
    // it should be FALSE now
    cout << "Is queue empty? ";
    if(priorityQueue->IsEmpty())
        cout << "TRUE";
    else
        cout << "FALSE";
    cout << endl;

    // Insert others elements
    priorityQueue->Insert(53);
    priorityQueue->Insert(8);
    priorityQueue->Insert(32);
    cout << "Insert 53, 8 and 32 to queue";
    cout << endl;

    // Peek the maximum element
    // It should be 53
    cout << "GetMax() = ";
    cout << priorityQueue->GetMax();
    cout << endl;

    // Extract maximum element
    cout << "ExtractMax() = ";
    cout << priorityQueue->ExtractMax();
    cout << endl;

    // Peek the maximum element
    // It should be 32 now
    cout << "GetMax() = ";
    cout << priorityQueue->GetMax();
    cout << endl;

    return 0;
}
