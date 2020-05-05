#include <iostream>
#include <cmath>
using namespace std;

int main() {
	// Define variables
	int n;
	float a;
	float b;
	int increasing_streak = 1;
	int max_streak = 0;

	// Ask user for input between 0 and 2147483647 (number of entries)
	cin >> n;

	// Check if input is valid
	if (n < 0 || n > 2147483647) {
		cout << "Invalid input" << endl;
		return 0;
	}

	// Asks user for n number of inputs between -1.79769 * 10^^308,1.79769*10^308

	cin >> a;
	if (n == 1) {
		cout << 1;
		return 0;
	}
	if (a < -1.79769 * pow(10, 308) || a > 1.79769 * pow(10, 308)) {
		cout << "Invalid input" << endl;
		return 0;
	}
	else {
		for (int i = 0; i < (n - 1); i++) {
			cin >> b;
			if (b < -1.79769 * pow(10, 308) || b > 1.79769 * pow(10, 308)) {
				cout << "Invalid input" << endl;
				return 0;
			}
			else {
				if (b > a) {
					increasing_streak += 1;
				}
				else {
					increasing_streak = 1;
				}
				if (increasing_streak >= max_streak) {
					max_streak = increasing_streak;
				}
				a = b;
			}
		}
		cout << endl;
	}
	cout << max_streak << endl;
}