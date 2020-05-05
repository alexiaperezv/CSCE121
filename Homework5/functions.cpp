#include <iostream>
#include <fstream>
#include "functions.h"
#include "provided.h"

using namespace std;

int readPrefs(char fileName[], int ngames, int prefs[]) {
  for (unsigned int i = 0; i <= MAX_NB_GAMES; ++i) {
    prefs[i] = 0;
  }
  ifstream ifs;
  ifs.open(fileName);
  if (!ifs) { // If file cannot be opened, return -1
    return -1;
  }

  int game_ID = 0;
  int game_rating = 0;
  int valid_items = 0;
  while(true) { 
    if((ifs >> game_ID >> game_rating).good() && (game_rating >= 0 && game_ID < MAX_NB_GAMES) && (game_rating >= 0 && game_rating <= 5)) {
      prefs[game_ID] = game_rating;
      valid_items++;
    }
     else {
       if (ifs.eof()) {
         break;
       }
      ifs.clear();
      ifs.ignore(1000, '\n');
    }
  }

  ifs.close();
  return valid_items;
}

int readPlan(char fileName[], int ngames, int plan[]) {
  ifstream ifs;
  ifs.open(fileName);
  if (!ifs) { 
    return -1;
  }
  int date = 0;
  int game_ID = 0;
  while(true) {
    if((ifs >> date >> game_ID).good() && (0 < date  && date <= 365) && (game_ID >= 0 && game_ID < MAX_NB_GAMES)) {
      plan[date] = game_ID;
    } else {
      if (ifs.eof()) {
        break;
      }
      ifs.clear();
      ifs.ignore(1000, '\n');
    }
  }
  return 0;
}

int computeFunLevel (int start, int duration, int gamePrefs[], int ngames, int plan[]) {
  int total_fun = 0;
  for (unsigned int i = start; i < (start + duration); ++i) {
    total_fun += gamePrefs[plan[i]];
  }
  return total_fun;
}

int findBestVacation (int duration,  int gamePrefs[], int ngames, int plan[]) {
  int best_start = 1;
  int best_score = -1;
  for (unsigned int i = 1; i <= 366 - duration;  ++i) {
    int total_funScore = computeFunLevel(i, duration, gamePrefs, ngames, plan);
    if (total_funScore > best_score) {
      best_start = i;
      best_score = total_funScore;
    }
  }
  return best_start;
}
