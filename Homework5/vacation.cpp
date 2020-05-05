#include <iostream>
#include "functions.h"
#include "provided.h"

using namespace std;

int main() {

    int ngames = 0;
	int duration = 0;

	cout << "Please enter ngames and duration: ";
	cin >> ngames;
	cin >> duration;
	if (ngames > 200 or ngames < 0 or duration > 365 or duration < 0) {
		cout << "Invalid input." << endl;
		return 0;
	}

	char game_titles[255];
	char game_preferences[255]; 
	char yearPlan[255];
	char gameTitles[MAX_NB_GAMES][MAX_TITLE_SIZE];
	int preferences[MAX_NB_GAMES + 1];
	int planned_days[366];

	cout << "Please enter name of file with titles: ";
	cin >> game_titles;
	cout << "Please enter name of file with preferences: ";
	cin >> game_preferences;
	cout << "Please enter name of file with plan: ";
	cin >> yearPlan;

	if (readGameTitles(game_titles, ngames, gameTitles) == -1 || readPrefs(game_preferences, ngames, preferences) == -1 || readPlan(yearPlan, ngames, planned_days) == -1) {
		cout << "Invalid file." << endl;
		return 0;
	}

	int prime_startDate = findBestVacation(duration, preferences, ngames, planned_days);
	cout << "Best start day is " << prime_startDate << endl;
	cout << "Games to be played:" << endl;
	printGamesPlayedInVacation(prime_startDate, duration, planned_days, gameTitles, ngames);
	
	return 0;

}
