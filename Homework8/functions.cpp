#include <iostream>
#include <string>

#include "functions.h"

using namespace std;


/* readTweet
 * Parameters:
 *      line: string containing the tweet information received by the function
 *      isRetweet: reference to bool; function will update it with true if retweet
 *      nb_htags: reference to int; function will update with number of hashtags
 *                in the tweet.
 *      array_of_htags: reference to an array of strings; function will allocate
 *                      the array and store the hashtag in it
 * Return value:
 *      none
 * Functionality:
 *     Processes the string in order to find out hashtags and identify if it is Retweet
 */
void readTweet(string line, bool& isRetweet, int& nb_htags, string*& array_of_htags) {

    // int coma_idx = line.find_first_of(",");

    // line.erase(0,coma_idx+1);

    string rt = line.substr(0,3);

    if(rt.find("RT") != string::npos){
        isRetweet = true;
    }

    else{
        isRetweet = false;
    }

    nb_htags = 0;

    for(int i = 0; i < line.length(); i++){
        if (line[i] == '#'){
            nb_htags++;
        }
    }

    array_of_htags = new string[nb_htags];

    int current_idx = 0;

    int idx = 0;

    while(line.find_first_of("#", current_idx) != string::npos){

        int ht_idx = line.find_first_of("#", current_idx);

        int space_idx = line.find_first_of(" \n", ht_idx);

        int ht_len = space_idx - ht_idx;

        string h = line.substr(ht_idx, ht_len);

        array_of_htags[idx] = h;

        idx++;

        current_idx = line.find_first_of("#", current_idx)+1;
    }

}


void sortList(OrderedHashtagList& ht_list){

    for(int i = 0; i < ht_list.size-1; i++){
        for(int j = 0; j < ht_list.size-i-1; j++){
            if(ht_list.list[j].counter < ht_list.list[j+1].counter){

                string ht = ht_list.list[j].name;
                int n = ht_list.list[j].counter;

                ht_list.list[j].name = ht_list.list[j+1].name;
                ht_list.list[j].counter = ht_list.list[j+1].counter;

                ht_list.list[j+1].name = ht;
                ht_list.list[j+1].counter = n;

            }
        }
    }

}



/* insertHashtag
 * Parameters:
 *      ht: string
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      true if insertion succeeds, false if memory allocation
 *      fails.
 * Functionality:
 *      See prompt for specification and examples.
 */

bool insertHashtag(string ht, OrderedHashtagList& hashlist) {

    for(int i = 1; i < ht.size(); i++){
        ht[i] = tolower(ht[i]);
    }


    if(hashlist.size == 0){

        hashlist.list[hashlist.size].name = ht;
        hashlist.list[hashlist.size].counter ++;
        hashlist.size++;
        return true;
    }

    for(int i = 0; i < hashlist.size; i++){

        if(hashlist.list[i].name == ht){
            hashlist.list[i].counter++;
            sortList(hashlist);
            return true;
        }
    }


    if(hashlist.size == hashlist.capacity){

        int n = hashlist.capacity*2;
        Hashtag* a = new Hashtag[n];
        for(int i = 0; i < hashlist.capacity; i++)
        {
            a[i].name = hashlist.list[i].name;
            a[i].counter = hashlist.list[i].counter;
        }
        delete [] hashlist.list;
        hashlist.capacity = n;

        hashlist.list = a;
    }



    hashlist.size ++;
    hashlist.list[hashlist.size-1].name = ht;
    hashlist.list[hashlist.size-1].counter ++;
    return true;
}

/* showMostPopularHashtags
 * Parameters:
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      none
 * Functionality:
 *      Prints the k most popular hashtags.
 *      See prompt for formatting details.
 */
void showMostPopularHashtags(OrderedHashtagList hashlist, int k) {

    if(hashlist.size == 0) {
        cout << "No hashtags." << endl;
    }
    else{
        if(k > hashlist.size) {
            k = hashlist.size;
        }
        for(int i = 0; i < k; i++) {
            cout << "Tag " << hashlist.list[i].name << " - " << hashlist.list[i].counter << " occurrence(s)" << endl;
        }
    }
}


