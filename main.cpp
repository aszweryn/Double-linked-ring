#include <iostream>
#include "ring.h"
using namespace std;

int main()
{
    Ring<int, int> a;
    cout << "Checking default constructor: ";
    a.print();

    cout << endl << "Checking push_front and printing the list:" << endl;
    a.push_front(8,7);
    a.print();

    cout << endl << "Checking clear method:" << endl;
    a.clear();
    a.print();

    cout << endl << "Adding more elements using push_front and :" << endl;
    a.push_front(1,1);
    a.push_front(2,2);
    a.push_front(3,3);
    a.push_front(4,4);
    a.push_front(5,5);
    a.print();

    cout << endl << "Checking find function:" << endl;
    Ring<int, int>::iterator itr;
    if(a.find(2, itr, 1))
        cout << "Node found!" << endl;


    cout << endl << "Checking getInfo and getKey:" << endl;
    a.find(1,itr,1);
    cout << "Key: " << itr.getKey() << endl;
    cout << "Info: " << itr.getInfo() << endl;
    a.find(5,itr,1);
    cout << "Key: " << itr.getKey() << endl;
    cout << "Info: " << itr.getInfo() << endl;

    cout << "Modifying keys and info of a node:" << endl;
    a.find(1,itr,1);
    itr.setInfo(420);
    cout << "Previous info = 1, now it is: " << itr.getInfo() << endl;
    itr.setKey(11);
    cout << "Previous key = 1, now it is: " << itr.getKey() << endl;


    cout << endl << "Checking remove iterator method: " << endl;
    a.remove(itr);
    a.print();

    cout << endl << "Checking remove method:" << endl;
    a.remove(5,1);
    a.remove(2,1);
    a.print();

    cout << endl << "Checking insertAfter:" << endl;
    a.insertAfter(4,6,9,1);
    a.insertAfter(6,7,8,1);
    a.print();
    a.clear();

    cout << endl << "Checking iterator insert method:" << endl;
    Ring<int, int>::iterator pos;
    a.push_front(1,2);
    a.push_front(3,4);
    a.insertAfter(1,7,8,1);
    a.find(7,pos,1);
    if(a.find(7,pos,1))
        cout << "Find function works" << endl;
    a.insertBefore(pos, 11,12);
    a.insertBefore(pos, 88,99);
    Ring<int, int>::iterator other;
    a.find(88, other, 1);
    a.insertBefore(other, 123, 321);
    a.insertBefore(other, 66,77);
    a.print();
    a.clear();

    return 0;
}