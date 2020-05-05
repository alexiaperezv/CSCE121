#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}


// implement for part 1

int* createSeam(int length) {
  int* seam = new int[length];
  for(int i = 0; i < length; i++)
  {
    seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  cout << "Loading image..." << endl;
  ifstream ifs (filename);
  if(!ifs.is_open()){
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  // If the image loads, we check that it is the right type
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  // If image loads and is right type, get width (w) and height (h) from preamble
  int w = 0;
  int h = 0;
  ifs >> w >> h;
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width <<  ") does not match value in file (" << w << ")"<< endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height <<  ") does not match value in file (" << h << ")"<< endl;
    return false;
  }
  // If image loads, is right type, and is right size, get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (colorMax != 255) {
    cout << "Error: invalid color value "<< colorMax << endl;
    return false;
  }

  // If image is right type, check that all int inputs are correct ASK BENJI
  /*
  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      Pixel p;
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.r;
      if(ifs.eof()){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.r < 0 || p.r > colorMax){
        cout << "Error: invalid color value " << p.r << endl;
        return false;
      }
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.g;
      if(ifs.eof()){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.g < 0 || p.g > colorMax){
        cout << "Error: invalid color value " << p.g << endl;
        return false;
      }
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.b;
      if(ifs.eof() && !ifs.good()){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.b < 0 || p.b > colorMax){
        cout << "Error: invalid color value " << p.b << endl;
        return false;
      }
      image[c][r] = p;
    }
  }
  if(!ifs.eof() || ifs.peek() != EOF){
    cout << "Error: too many color values" << endl;
    return false;
  }
  ifs.close();
  return true;
  */

  /*
  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      Pixel p;
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.r;
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.r < 0 || p.r > colorMax){
        cout << "Error: invalid color value " << p.r << endl;
        return false;
      }
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.g;
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.g < 0 || p.g > colorMax){
        cout << "Error: invalid color value " << p.g << endl;
        return false;
      }
      if(ifs.peek() == EOF){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs.clear();
      ifs >> p.b;
      if(ifs.fail()){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if(p.b < 0 || p.b > colorMax){
        cout << "Error: invalid color value " << p.b << endl;
        return false;
      }
      image[c][r] = p;
    }
  }
  if(!ifs.eof() || ifs.peek() != EOF){
    cout << "Error: too many color values" << endl;
    return false;
  }
  ifs.close();
  return true;
  */

  
  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      Pixel p;
      if(ifs.eof()){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs >> p.r;
      if(!ifs.good()){
      cout << "Error: read non-integer value" << endl;
      return false;
      }
      if(p.r < 0 || p.r > colorMax){
        cout << "Error: invalid color value " << p.r << endl;
        return false;
      }
      if(ifs.eof()){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs >> p.g;
      if(!ifs.good()){
      cout << "Error: read non-integer value" << endl;
      return false;
      }
      if(p.g < 0 || p.g > colorMax){
        cout << "Error: invalid color value " << p.g << endl;
        return false;
      }
      if(ifs.eof() && r != height-1 && c != width-1){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      ifs >> p.b;  
      if(!ifs.good() && r != height-1 && c != width-1){
      cout << "Error: read non-integer value" << endl;
      return false;
      }
      if(p.b < 0 || p.b > colorMax){
        cout << "Error: invalid color value " << p.b << endl;
        return false;
      }
      image[c][r] = p;
    }
  }
  int eof;
  ifs >> eof;
  if(!ifs.eof()){
    cout << "Error: too many color values" << endl;
    return false;
  }
  ifs.close();
  return true;
  
}


bool outputImage(string filename, Pixel** image, int width, int height) {
  cout << "Outputting image..." << endl;
	ofstream ofs(filename);
	// check if output stream opened successfully
	if (!ofs.is_open()) {
		cout << "Error: failed to open output file - " << filename << endl;
    return 1;
	}
	else {
		// output preamble
		ofs << "P3\n";
		ofs << width << " " << height << "\n";
		ofs << 255 << "\n";

		// output pixels
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				ofs << image[j][i].r << " ";
				ofs << image[j][i].g << " ";
				ofs << image[j][i].b << " ";
			}
		}
	}
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
  int x_gradient2;
  if(x == 0){
    int red_x = image[x+1][y].r - image[width -1][y].r; 
    int green_x = image[x+1][y].g - image[width -1][y].g; 
    int blue_x = image[x+1][y].b - image[width -1][y].b; 
    x_gradient2 = pow(red_x, 2) + pow(green_x, 2) + pow(blue_x, 2);
  }
  else if(x == width -1){
    int red_x = image[0][y].r - image[x-1][y].r; 
    int green_x = image[0][y].g - image[x -1][y].g; 
    int blue_x = image[0][y].b - image[x -1][y].b; 
    x_gradient2 = pow(red_x, 2) + pow(green_x, 2) + pow(blue_x, 2);
  }
  else{
    int red_x = image[x+1][y].r - image[x -1][y].r; 
    int green_x = image[x+1][y].g - image[x -1][y].g; 
    int blue_x = image[x+1][y].b - image[x -1][y].b; 
    x_gradient2 = pow(red_x, 2) + pow(green_x, 2) + pow(blue_x, 2);
  }

  int y_gradient2;
  if(y == 0){
    int red_y = image[x][y + 1].r - image[x][height -1].r; 
    int green_y = image[x][y +1].g - image[x][height -1].g; 
    int blue_y = image[x][y+1].b - image[x][height -1].b; 
    y_gradient2 = pow(red_y, 2) + pow(green_y, 2) + pow(blue_y, 2);
  }
  else if(y == height -1){
    int red_y = image[x][0].r - image[x][y-1].r; 
    int green_y = image[x][0].g - image[x][y -1].g; 
    int blue_y = image[x][0].b - image[x][y -1].b; 
    y_gradient2 = pow(red_y, 2) + pow(green_y, 2) + pow(blue_y, 2);
  }
  else{
    int red_y = image[x][y + 1].r - image[x][y -1].r; 
    int green_y = image[x][y +1].g - image[x][y -1].g; 
    int blue_y = image[x][y+1].b - image[x][y -1].b; 
    y_gradient2 = pow(red_y, 2) + pow(green_y, 2) + pow(blue_y, 2);
  }

  return (x_gradient2 + y_gradient2);
}

// implement for part 2

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  
  int total_energy = energy(image, 0, start_col, width, height)
  
  //set seam for the first row (0) to the starting column start_col
  
  return total_energy;
}
int* findMinVerticalSeam(Pixel** image, int width, int height) {
  return nullptr;
}
void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
}

/*
int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  return 0;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  return nullptr;
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
}*/