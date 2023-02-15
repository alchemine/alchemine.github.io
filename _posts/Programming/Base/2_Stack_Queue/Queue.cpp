// https://github.com/PacktPublishing/CPP-Data-Structures-and-Algorithms/blob/master/Chapter03/Queue/include/Queue.h

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
  T Value;
  Node<T> * Next;
  Node(T value) : Value(value), Next(NULL) {}
};

template <typename T>
class Queue {
private:
  int m_count;
  Node<T>* m_front;
  Node<T>* m_back;

public:
  Queue() : m_count(0), m_front(NULL), m_back(NULL) {}

  bool IsEmpty() { return m_count <= 0; }

  T Front() { return m_front->Value; }

  void Enqueue(T val) {
    Node<T>* node = new Node<T>(val);
    if(m_count == 0) {
      node->Next = NULL;
      m_front = node;
      m_back  = m_front;
    }
    else {
      m_back->Next = node;
      m_back = node;
    }
    m_count++;
  }

  void Dequeue() {
    if(m_count == 0)
      return;
    Node<T>* node = m_front;
    m_front = m_front->Next;
    delete node;
    m_count--;
  }
};


int main()
{
    // NULL
    Queue<int> queueInt = Queue<int>();

    // Enqueue several numbers to the queue
    queueInt.Enqueue(35);
    queueInt.Enqueue(91);
    queueInt.Enqueue(26);
    queueInt.Enqueue(78);
    queueInt.Enqueue(44);
    queueInt.Enqueue(12);

    // list the element of queue
    while(!queueInt.IsEmpty())
    {
        // Get the front element
        cout << queueInt.Front() << " - ";

        // Remove the front element
        queueInt.Dequeue();
    }
    cout << "END" << endl;

    return 0;
}
