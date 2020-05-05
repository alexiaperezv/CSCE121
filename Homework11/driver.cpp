#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
    DoublyLinkedList<int> l1 = DoublyLinkedList<int>();
    for(int i = 1; i <= 10; i++)
        l1.push_back(i);
    DoublyLinkedList<int> l2 = l1;
    DoublyLinkedList<int> l3 = DoublyLinkedList<int>();
    l3 = l2;

    cout << l1 << endl;
    cout << l2 << endl;
    cout << l3 << endl;

    if(l1 == l2)
        cout << "Equal" << endl;
    else
        cout << "Not Equal" << endl;
    
    l1.insert(20, 0);
    l1.insert(30, 5);
    l1.insert(40, l1.size()-1);
    l1.insert(50, l1.size());
    cout << l1 << endl;
    
    return 0;
}