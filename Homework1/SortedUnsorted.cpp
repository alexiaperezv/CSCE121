
#include <iostream>
using namespace std;

int main() {

  int input = 1, previous = 0, count = 0;
  bool ascending = true, descending = true;
  cin >> input;
  if (input == 0) {
      cout << "empty";
      return 0;
    }
  while (input != 0){
    if (count == 0) {
      previous = input;
    }
    else {
      if (input > previous) {
          descending = false;
      }
      else if ( input < previous){
          ascending = false;
      }  
    }
    count++;
    cin >> input;
  }

  if(ascending || descending) {
    cout << count << " sorted" << endl;
  } 
  else {
    cout<< count << " unsorted" << endl;
  }

  return 0;
}