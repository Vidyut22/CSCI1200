// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333333, "george");
  add(phonebook, 2222222, "vidyut");
  add(phonebook, 1111111, "tommy");
  add(phonebook, 4444444, "george");
  add(phonebook, 5555555, "vidyut");
  add(phonebook, 6666666, "tommy");
  add(phonebook, 7777777, "george");
  add(phonebook, 8888888, "vidyut");
  add(phonebook, 9999999, "tommy");
  //add(phonebook, 3333333333, "hweufh");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  identify(phonebook, 3333333);
  identify(phonebook, 2222222);
  identify(phonebook, 4444444);
  identify(phonebook, 5555555);
  identify(phonebook, 6666666);
  identify(phonebook, 7777777);
  identify(phonebook, 8888888);
  identify(phonebook, 9999999);
  
  //identify(phonebook, 3333333333);
}
