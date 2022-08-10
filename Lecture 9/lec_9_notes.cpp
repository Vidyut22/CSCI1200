#include <iostream>
#include <list>
#include <cassert>


void exercise_9_13(std::list<int> &lst, int x) {
  
  // we'll use 2 iterators...
  std::list<int>::iterator itr;
  std::list<int>::iterator itr2;
 

  // 1) remove all negative numbers from lst
  itr = lst.begin();
  while (itr != lst.end()) {
    if (*itr < 0) {
      // NOTE: with this erase call & return value, the iterator will
      //       advance to the next element!
      itr = lst.erase(itr);
      // caution: don't try a trick with itr-- and then itr++ 
      // it won't work (on all platforms) when you are erasing the first element
    } else {
      // only advance the iterator if this element was not erased
      itr++;
    }
  }


  // 2) verify the elements are sorted in increasing order
  if (lst.size() > 0) {
    // these 2 iterators will point at adjacent elements
    itr = lst.begin();
    itr2 = lst.begin();
    ++itr2;
    while (itr2 != lst.end()) {
      // program will crash if the list is not sorted
      assert (*itr <= *itr2);
      itr++;
      itr2++;
    }
    /*
     *  Alternative to the while loop
    for (; itr2 != lst.end(); itr++, itr2++){
      assert (*itr <= *itr2);
    }
     */
  }


  // 3) insert x into the list 
  itr = lst.begin();
  bool found = false;
  while (itr != lst.end()) {
    if (*itr > x) {
      // if we reach an element greater than x, insert just before
      // that element and break the loop
      lst.insert (itr , x);
      found = true;
      break;
    } else {
      itr++;
    }
  }
  // if we didn't find an element greater than x, then this element
  // belongs at the end of the list
  if (!found) {
    lst.push_back(x);
    //Alternately, lst.insert(itr, x);
  }
}





int main() {
  std::list<int> test;

  test.push_back(-1);
  test.push_back(-1);
  test.push_back(2);
  test.push_back(-1);
  test.push_back(-1);
  test.push_back(4);
  test.push_back(-1);
  test.push_back(-1);
  test.push_back(-1);
  //test.push_back(10);
  test.push_back(6);
  test.push_back(-1);
  test.push_back(-1);
  test.push_back(8);
  test.push_back(-1);
  test.push_back(-1);

  exercise_9_13(test,1);
  //exercise_9_13(test,5);
  //exercise_9_13(test,9);

  for (std::list<int>::iterator itr = test.begin(); itr != test.end(); ++itr) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;

}
