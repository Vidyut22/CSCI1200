//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>
#include "unrolled.h"
using namespace std;
// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }
  //a.print(std::cout);
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() 
{
    cout << "--------------STUDENT TESTS------------------\n\n\n\n" << endl;
    UnrolledLL<int> a;
    list<int> b;
    for (int i = 1; i < 38; ++i) {
        a.push_back(i);
        b.push_back(i);
    }
    UnrolledLL<int>::iterator a_iter = a.begin();
    std::list<int>::iterator b_iter = b.begin();
    // iterate through the integers and print them out
    std::cout << "the integers from 1>37" << std::endl;
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
        std::cout << " " << *itr;
    }

    //TESTING SPECIAL ERASE CASES
    cout << "\n" << endl;
    std::cout << "-----------ALL ERASE TESTS----------" << std::endl;
    cout << endl;
    //erasing 5 elements in middle
    std::cout << "ERASING 5 ELEMENTS, 20-24" << std::endl;
    a_iter = a.begin();
    while (a_iter != a.end()) {
        if (*a_iter == 20 || *a_iter == 21 || *a_iter == 22|| *a_iter == 23|| *a_iter == 24) {
            a_iter = a.erase(a_iter);
        }
        else {
            a_iter++;
        }
    }
    b_iter = b.begin();
    while (b_iter != b.end()) {
        if (*b_iter == 20 || *b_iter == 21 || *b_iter == 22 || *b_iter == 23 || *b_iter == 24) {
            b_iter = b.erase(b_iter);
        }
        else {
            b_iter++;
        }
    }
    a.print(std::cout);
    std::cout << std::endl;
    assert(SAME(a, b));

    //erasing last element in node
    std::cout << "ERASING 1 ELEMENT 19 | ALSO DELETES NODE" << std::endl;
    a_iter = a.begin();
    while (a_iter != a.end()) {
        if (*a_iter == 19 ||*a_iter == 20 || *a_iter == 21 || *a_iter == 22 || *a_iter == 23 || *a_iter == 24) {
            a_iter = a.erase(a_iter);
        }
        else {
            a_iter++;
        }
    }
    b_iter = b.begin();
    while (b_iter != b.end()) {
        if (*b_iter == 19 ||*b_iter == 20 || *b_iter == 21 || *b_iter == 22 || *b_iter == 23 || *b_iter == 24) {
            b_iter = b.erase(b_iter);
        }
        else {
            b_iter++;
        }
    }
    a.print(cout);
    assert(SAME(a, b));
    cout << endl;

    //erase last element in list
    std::cout << "ERASING LAST ELEMENT| ALSO DELETES NODE" << std::endl;
    a_iter = a.begin();
    while (a_iter != a.end()) {
        if (*a_iter ==37) {
            a_iter = a.erase(a_iter);
        }
        else {
            a_iter++;
        }
    }
    b_iter = b.begin();
    while (b_iter != b.end()) {
        if (*b_iter == 37) {
            b_iter = b.erase(b_iter);
        }
        else {
            b_iter++;
        }
    }
    a.print(std::cout);
    std::cout << std::endl;
    assert(SAME(a, b));

    UnrolledLL<int> c;
    c.push_back(1);
    UnrolledLL<int>::iterator c_iter = c.begin();

    //erase last element remaining in list
    cout << "ERASING LIST OF SIZE 1 | NO NODES SHOULD REMIAN" << endl;
    cout << "List of size 1:"<< endl;
    c.print(cout);
    c_iter = c.erase(c_iter);
    c.print(cout);
    cout << "------ALL ERASE TESTS COMPLETE------" << endl;


    //TESTING SPECIAL INSERT CASES
    cout << "\n\n----------ALL INSERT TESTS----------" << endl;
    a.clear();
    b.clear();

    //inserting to empty list
    cout << "INSERT ELEMENT AT BEGGINING OF EMPTY LIST" << endl;
    a.insert(a.begin(), 1);
    b.insert(b.begin(), 1);
    a.print(cout);
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
    {
        if (*itr == 2) {
            itr = a.insert(itr, 77);
            itr++;
        }
    }
    for (list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        if (*itr == 2) {
            itr = b.insert(itr, 77);
            itr++;
        }
    }
    assert(SAME(a, b));
    cout << endl;
    //insert elements to end of list
    cout << "INSERT ELEMENTS AT END OF LIST" << endl;
    for (int i = 30; i < 64; ++i) {
        a.push_back(i);
        b.push_back(i);
    }
    a.print(cout);
    cout << endl;

    //insert element to overflow node
    cout << "TEST OVERFLOW ELEMENTS IN NODE | INSERT #42 BEFORE 56" << endl;
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
    {
        if (*itr == 56) {
            itr = a.insert(itr, 42);
            itr++;
        }
    }
    for (list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        if (*itr == 56) {
            itr = b.insert(itr, 42);
            itr++;
        }
    }
    assert(SAME(a, b));
    a.print(cout);
    cout << endl;
    //insert element to overflow node and needs to create new node at end
    cout << "TEST OVERFLOW ELEMENTS IN NODE | INSERT #42 BEFORE 32 | SHOULD CREATE NEW NODE AT END FOR 63" << endl;
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
    {
        if (*itr == 32) {
            itr = a.insert(itr, 42);
            itr++;
        }
    }
    for (list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        if (*itr == 32) {
            itr = b.insert(itr, 42);
            itr++;
        }
    }
    assert(SAME(a, b));
    a.print(cout);
    cout << endl;

    //COMBO
    std::cout << "ERASING 3 ELEMENTS, 42-44 AND INSERTING 90 BEFORE 45" << std::endl;

    cout << "Erased elements" << endl;
    a_iter = a.begin();
    while (a_iter != a.end()) {
        if (*a_iter == 42 || *a_iter == 43 || *a_iter == 44) {
            a_iter = a.erase(a_iter);
        }
        else {
            a_iter++;
        }
    }
    b_iter = b.begin();
    while (b_iter != b.end()) {
        if (*b_iter == 42 || *b_iter == 43 || *b_iter == 44) {
            b_iter = b.erase(b_iter);
        }
        else {
            b_iter++;
        }
    }
    a.print(std::cout);
    assert(SAME(a, b));
    cout << endl;
    cout << "Inserted 90 before 45" << endl;
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
    {
        if (*itr == 45) {
            itr = a.insert(itr, 90);
            itr++;
        }
    }
    for (list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        if (*itr == 45) {
            itr = b.insert(itr, 90);
            itr++;
        }
    }
    assert(SAME(a, b));
    a.print(cout);
    cout << endl;

    //insert at end
    cout << "NORMAL INSERTION AT END" << endl;
    for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
    {
        if (*itr == 63) {
            itr = a.insert(itr, 22);
            itr++;
        }
    }
    for (list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        if (*itr == 63) {
            itr = b.insert(itr, 22);
            itr++;
        }
    }
    assert(SAME(a, b));
    a.print(cout);
    cout << endl;
    cout << "-----ALL INSERT TESTS COMPLETE------" << endl;


    //TESTING DIFFERENT TYPES
    cout << "\n\n---------TYPE TESTS---------" << endl;
    cout << "------------------" << endl;
    UnrolledLL<string> f;
    UnrolledLL<char> g;
    UnrolledLL<int> h;
    for (int i = 0; i < 30; i++)
    {
        f.push_back("test");
        g.push_back('A');
        h.push_back(22);
    }
    cout << "STRING LIST" << endl;
    f.print(cout);
    cout << endl;
    cout << "CHARACTER LIST" << endl;
    g.print(cout);
    cout << endl;
    cout << "INTEGER LIST" << endl;
    h.print(cout);
    cout << "-------TYPE TESTS COMPLETE-------" << endl;
}
