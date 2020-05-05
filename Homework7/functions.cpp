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
  int* seam = new int[length]; //new array in the heap
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
  ifs >> type; // reads the first line in the file, should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  // If image loads and is right type, get width (w) and height (h) from preamble
  int w = 0;
  int h = 0;
  ifs >> w >> h; //reads next 2 numbers in the file (after the type)
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
  ifs >> colorMax; //Next line is the max color value
  if (colorMax != 255) {
    cout << "Error: invalid color value "<< colorMax << endl;
    return false;
  }

  int val;
  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      Pixel p;
      for(int i = 0; i < 3; i++)
      {
          ifs >> val;
          if(ifs.fail() && ifs.eof()){
            cout << "Error: not enough color values" << endl;
            return false;
          }
          if(!ifs.good()){
            cout << "Error: read non-integer value" << endl;
            return false;
          }
          if(val < 0 || val > colorMax){
            cout << "Error: invalid color value " << val << endl;
            return false;
          }
          switch(i){
            case(0):
              p.r = val;
              break;
            case(1):
              p.g = val;
              break;
            case(2):
              p.b = val;
              break;
            default:
              break;
          }
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

// uncomment for part 2


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  seam[0] = start_col;
  int totalEnergy = energy(image, start_col, 0, width, height);
  int col = start_col;
  for(int r = 1; r < height; r++)
  {
    if(col == 0)
	  {
      int straight = energy(image, col, r, width, height);
      int left = energy(image, col+1, r, width, height);
		  if(straight <= left)
      {
        totalEnergy += straight;
      }
		  else
      {
        totalEnergy += left;
        col = col+1;
      }
	  }
	  else if(col == width-1)
	  {
      int straight = energy(image, col, r, width, height);
      int right = energy(image, col-1, r, width, height);
		  if(straight <= right)
      {
        totalEnergy += straight;
      }
		  else
      {
        totalEnergy += right;
        col = col-1;
      }
	  }
	  else
	  {
      int straight = energy(image, col, r, width, height);
      int left = energy(image, col+1, r, width, height);
		  int right = energy(image, col-1, r, width, height);
      if(right < left && right < straight)
      {
        totalEnergy += right;
        col = col-1;
      }
		  else if(left < straight)
      {
        totalEnergy += left;
        col = col+1;
      }
      else
      {
        totalEnergy += straight;
      }
	  }
    seam[r] = col;
  }
  return totalEnergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  seam[0] = start_row;
  int totalEnergy = energy(image, 0, start_row, width, height);
  int row = start_row;
  for(int c = 1; c < width; c++)
  {
    if(row == 0)
	  {
      int straight = energy(image, c, row, width, height);
      int right = energy(image, c, row+1, width, height);
		  if(straight <= right)
      {
        totalEnergy += straight;
      }
		  else
      {
        totalEnergy += right;
        row = row+1;
      }
	  }
	  else if(row == height-1)
	  {
      int straight = energy(image, c, row, width, height);
      int left = energy(image, c, row-1, width, height);
		  if(straight <= left)
      {
        totalEnergy += straight;
      }
		  else
      {
        totalEnergy += left;
        row = row-1;
      }
	  }
	  else
	  {
      int straight = energy(image, c, row, width, height);
      int left = energy(image, c, row-1, width, height);
		  int right = energy(image, c, row+1, width, height);
      if(right < left && right < straight)
      {
        totalEnergy += right;
        row = row+1;
      }
		  else if(left < straight)
      {
        totalEnergy += left;
        row = row-1;
      }
      else
      {
        totalEnergy += straight;
      }
	  }
    seam[c] = row;
  }
  return totalEnergy;
}
 
int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* seam = createSeam(height);
  int minCol = 0;
  for(int c = 1; c < width; c++)
  {
    if(loadVerticalSeam(image, c, width, height, seam) < loadVerticalSeam(image, minCol, width, height, seam))
    {
      minCol = c;
    }    
  }
  loadVerticalSeam(image, minCol, width, height, seam);
  return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int* seam = createSeam(width);
  int minRow = 0;
  for(int r = 1; r < height; r++)
  {
    if(loadHorizontalSeam(image, r, width, height, seam) < loadHorizontalSeam(image, minRow, width, height, seam))
    {
      minRow = r;
    }    
  }
  loadHorizontalSeam(image, minRow, width, height, seam);
  return seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for(int r = 0; r < height; r++)
  {
    for(int c = verticalSeam[r]; c < width-1; c++)
    {
      image[c][r] = image[c+1][r];
    }
  }
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for(int c = 0; c < width; c++)
  {
    for(int r = horizontalSeam[c]; r < height-1; r++)
    {
      image[c][r] = image[c][r+1];
    }
  }
}