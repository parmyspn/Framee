/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include <iostream>
#include <vector>


#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "imglist.h"

#include <filesystem>

using namespace std;


int enterMeasure(string message){
  double measure;
  cout << message << endl;
  cin >> measure;
  return measure;
}

void exitMessage(string message) {
  cout << message << endl;
  exit (EXIT_FAILURE);
}

string mainMenu(){
  string adjustment;
  cout << "Please enter the adjustment:\n" << "\t1.Reduce noise\n" <<"\t2.Export image\n" << endl;
  cin >> adjustment;
  return  adjustment;
}

string getParentDirectory(){
  string dir =   __fs::filesystem::current_path();
  dir = dir.replace(dir.find("Noise-Reduction"),15, "");
  return dir;
}

int main() {
  cs221util::PNG png;
   
  string fileName;
  cout << "Enter the file name of the picture" << endl;
  cin >> fileName;

  cout << "Importing image..." << endl;
  png.readFromFile(getParentDirectory()+ "input-images/" + fileName);

  string adjustment = mainMenu();
  unsigned int carvedPixels;
  unsigned int selectionMode;
  int flag = 1;
  bool fill = false;

  ImgList list(png);

  while(flag == 1)
    switch(stoi(adjustment)){
      case 1:
        //carvedPixels = enterMeasure("Please enter the number of noised pixels you want to reduce: ");
        selectionMode = enterMeasure("Please enter noise selection mode:\n 1.Least luminance\n 2.Maximum color difference\n" );
        list.Carve(5, selectionMode-1);
        fill = true;
        adjustment = mainMenu();
        break;
      case 2:
        flag = 0;
        png = list.Render(fill , 0);
        break;
      default:
        exitMessage("No Valid Operation");
        break;
    }

  cout << "Exporting image..." << endl;
  png.writeToFile(getParentDirectory() +"/exported-images/out-" + fileName );
  cout << "You can find your exported image in the \'exported-images\' folder" << endl;


   return 0;
}
