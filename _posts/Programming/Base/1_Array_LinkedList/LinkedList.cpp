// https://github.com/PacktPublishing/CPP-Data-Structures-and-Algorithms/tree/master/Chapter02/Singly_Linked_List

#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
  T Value;
  Node<T> * Next;
  Node(T value) : Value(value), Next(NULL) {}
};


template <typename T>
class LinkedList
{
private:
  int m_count;

public:
  Node<T> * Head;  // Null if empty
  Node<T> * Tail;  // Null if empty

  LinkedList() : m_count(0), Head(NULL), Tail(NULL) {}

  // Get() operation
  Node<T> * Get(int index)
  {
    if(index < 0 || index > m_count)
      return NULL;
    Node<T> * node = Head;
    for(int i = 0 ; i < index; ++i)
      node = node->Next;
    return node;
  }

  // Insert() operation
  void InsertHead(T val)
  {
    Node<T> * node = new Node<T>(val);
    node->Next = Head;
    Head = node;
    if(m_count == 0)
      Tail = Head;
    m_count++;
  }
  void InsertTail(T val)
  {
    if(m_count == 0)
    {
      InsertHead(val);
      return;
    }
    Node<T> * node = new Node<T>(val);
    Tail->Next = node;
    Tail = node;
    m_count++;
  }
  void Insert(int index, T val)
  {
    if(index < 0 || index > m_count)
      return;
    if(index == 0)
      InsertHead(val);
    else if(index == m_count)
      InsertTail(val);
    else
    {
      Node <T> * prevNode = Head;
      for(int i = 0 ; i < index - 1 ; ++i)
        prevNode = prevNode->Next;
      Node<T> * nextNode = prevNode->Next;
      Node<T> * node = new Node<T>(val);
      node->Next = nextNode;  //             node -> nextNode
      prevNode->Next = node;  // prevNode -> node
      m_count++;
    }
  }
  
  // Search() operation
  int Search(T val)
  {
    if(m_count == 0)
      return -1;
    int index = 0;
    Node<T> * node = Head;
    while(node->Value != val)
    {
      index++;
      node = node->Next;
      if(node == NULL)  // not found
        return -1;
    }
    return index;
  }
  
  // Remove() operation
  void RemoveHead()
  {
    if(m_count == 0)
      return;
    Node<T> * node = Head;
    Head = Head->Next;
    delete node;
    m_count--;
  }
  void RemoveTail()
  {
    if(m_count == 0)
      return;
    else if(m_count == 1)
      RemoveHead();
    else
    {
      Node<T> * prevNode = Head;
      Node<T> * node = Head->Next;
      while(node->Next != NULL)
      {
        prevNode = prevNode->Next;
        node     = node->Next;
      }
      prevNode->Next = NULL;  // 1. Remove connection
      Tail = prevNode;        // 2. Update Tail
      delete node;            // 3. Remove node
      m_count--;
    }
  }
  void Remove(int index)
  {
    if(m_count == 0)
      return;
    if(index < 0 || index >= m_count)
      return;
    if(index == 0)
      RemoveHead();
    else if(index == m_count-1)
      RemoveTail();
    else
    {
      Node<T> * prevNode = Head;
      for(int i = 0 ; i < index-1 ; ++i)
        prevNode = prevNode->Next;
      Node<T> * node = prevNode->Next;
      Node<T> * nextNode = node->Next;
      prevNode->Next = nextNode;
      delete node;
      m_count--;
    }
  }
  
  // Additional operation
  int Count() { return m_count; }
  void PrintList()
  {
    Node<T> * node = Head;
    while(node != NULL)
    {
      cout << node->Value << " -> ";
      node = node->Next;
    }
    cout << "NULL" << endl;
  }
};


int main()
{
  LinkedList<int> linkedList = LinkedList<int>();
  linkedList.InsertHead(43);
  linkedList.InsertHead(76);
  linkedList.InsertHead(15);
  linkedList.InsertHead(44);
  linkedList.PrintList();
  
  linkedList.Insert(4, 100);
  linkedList.Insert(3, 48);
  linkedList.Insert(0, 22);
  linkedList.PrintList();

  cout << "Get value of the second index: ";
  Node<int> * get = linkedList.Get(2);
  if(get != NULL)
    cout << get->Value << endl;
  else
    cout << "not found" << endl;
  
  cout << "The position of value 15: ";
  cout << linkedList.Search(15) << endl;
  
  cout << "Remove the first element: ";
  linkedList.Remove(0);
  linkedList.PrintList();
  
  cout << "Remove the fifth element: ";
  linkedList.Remove(4);
  linkedList.PrintList();
  
  return 0;
}