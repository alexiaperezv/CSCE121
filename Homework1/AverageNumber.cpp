#include <iostream>
using namespace std;


int main() {
  float num = 0;
  float sum = 0;
  int count = 0;
  cin >> num;
  if(num == 0){
    cout << "empty";
  }
  else{
    while(num != 0){
        sum += num;
        cin >> num;
        count += 1;
    }
    float average = sum/count;
    cout << "avg: " << average;
    
  }
  
  return 0;
}