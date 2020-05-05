#include <iostream>
using namespace std;

int main(){
    
    // First, declare variables
    
    int dollars,cents ,change, quarters, dimes, nickels, pennies, coins;
    
    // Second, ask for input
    
    cout << "Enter dollars: ";
    cin >> dollars;
    
    cout << "Enter cents: ";
    cin >> cents;
    
    // Third, Operations
   
    change = (dollars*100) + cents;
    quarters = change/25;
    dimes = (change%25)/10;
    nickels = ((change%25)%10)/5;
    pennies = ((change%25)%10)%5;
    coins = quarters + dimes + nickels + pennies;
    
	// Last, Output
    
	cout << "Pennies: " << pennies << endl;
	cout << "Nickels: " << nickels << endl;
	cout << "Dimes: " << dimes << endl;
    cout << "Quarters: " << quarters << endl;
    cout << "Total coins used: " << coins << endl;
    
    return 0;
}