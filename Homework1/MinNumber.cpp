
#include <iostream>
using namespace std;


int main() {
  int num = 0;
  int min = 0;
  cin >> num;
  if(num == 0){
    cout << "empty";
  }
  else{
    min = num;
    while(num != 0){
        if(num < min){
            min = num;
        }
        cin >> num;
    }
    cout << "min: " << min;
  }
  
  return 0;
}