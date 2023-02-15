// https://github.com/PacktPublishing/CPP-Data-Structures-and-Algorithms/tree/master/Chapter02/Array

#include <iostream>
using namespace std;


int main()
{
  int arr[] = { 21, 47, 87, 35, 92 };
  
  cout << "Array elements: ";
  for(int i = 0 ; i < sizeof(arr)/sizeof(*arr) ; ++i)
    cout << arr[i] << " ";
  cout << endl;
  
  return 0;
}