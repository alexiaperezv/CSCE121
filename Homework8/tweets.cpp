#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "functions.h"

/* Starter code: used by function printMenu */
void printLine(string msg) {
    cout << msg << endl;
}

/* Starter code: function printMenu() is ready for you */
void printMenu() {
    cout << endl;
    printLine("Welcome to Aggieland Twitter Feeds Stats");
    printLine("The options are:");
    printLine("1. load tweet data file and update stats");
    printLine("2. show overall stats (number of tweets, retweets, and hashtags)");
    printLine("3. show most popular hashtags");
    printLine("9. quit");
    cout << "--------> Enter your option: ";
}

/* Starter code: function to read option from the user is ready for you */
int getOption() {
    int option;
    cin >> option;
    if (cin.fail()) {
	cin.clear();
	cin.ignore(256, '\n');
	return -1;
    } else {
	cin.ignore(256, '\n');
    }
    return option;
}

int main() {

    printMenu();

    int option = getOption();

    string line;

    bool isRT;

    int nb_htags;

    int tweets = 0;

    int reTweets = 0;

    int hashtags = 0;

    string* str_list;

    OrderedHashtagList ht_list;

    while(option != 9){

        if(option == 1){
            string filename;
            cout << "Enter filename: ";
            cin >> filename;

            ifstream fin;
            fin.open(filename);

            if (!fin){
                cout << "File can't be open." << endl;
            }

            string date;

            while(getline(fin, date, ',')){
                if(fin.eof()){
                    break;
                }

            tweets ++;
            getline(fin, line, '\n');
            readTweet(line, isRT, nb_htags, str_list);

            if(isRT == true){
                reTweets += 1;
            }

            for(int i = 0; i < nb_htags; i++){
                insertHashtag(str_list[i], ht_list);
            }

            delete [] str_list;
            }
        }
        else if(option == 2){
            cout << "Tweets: " << tweets << ", Retweets: " << reTweets << ", Hashtags: " << ht_list.size << endl;
        }

        else if(option == 3)
        {
            showMostPopularHashtags(ht_list, 10);
        }

        else{
        cout << "Invalid option" << endl;
        }

        printMenu();
        option = getOption();
    }

    delete [] ht_list.list;
    return 0;
}

