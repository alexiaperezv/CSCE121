#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
  // Add code to validate input (Do in part 1)
  cout << "Input filename: ";
  cin >> filename;
  cout << "Input width and height: ";
  cin >> width;
  if(!cin.good()){
    cout << "Error: width is a non-integer value" << endl;
    return 1;
  }
  cin >> height;
  if(!cin.good()){
    cout << "Error: height is a non-integer value" << endl;
    return 1;
  }

  Pixel** image = createImage(width, height); // create array of size that we need
  if (image != nullptr) {
    cout << "empty image:" << endl;
    for(int r = 0; r < height; r++){
       for(int c = 0; c < width; c++){
          cout << image[c][r].r << " " << image[c][r].g << " " << image[c][r].b << " ";
       }
       cout << endl;
    }
    cout << endl;
    if (loadImage(filename, image, width, height)) {
      cout << "image:" << endl;
      for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            cout << image[c][r].r << " " << image[c][r].g << " " << image[c][r].b << " ";
        }
        cout << endl;
      }
      cout << endl;
      cout << "energies:" << endl;
      for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            cout << energy(image, c, r, width, height) << " ";
        }
        cout << endl;
      }
    }
  
    // call last to remove the memory from the heap
    deleteImage(image, width);
  }
}