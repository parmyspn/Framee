/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
**/

#include <iostream>
#include <vector>
#include "cs221util/catch.hpp"

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"

#include "ptree.h"
#include "hue_utils.h"
#include <filesystem>

using namespace std;


double enterMeasure(){
  double measure;
  cout << "Please enter the prune rate "  << endl;
  cin >> measure;
  return measure;
}

void exitMessage(string message) {
  cout << message << endl;
  exit (EXIT_FAILURE);
}

string mainMenu(){
  string adjustment;
  cout << "Please enter the Adjustment:\n" << "\t1.Compress image\n" <<"\t2.Flip horizontally\n" <<"\t3.Flip Vertically\n"  <<"\t4.Export image\n" << endl;
  cin >> adjustment;
  return  adjustment;
}

string getParentDirectory(){
  string dir =   __fs::filesystem::current_path();
  dir = dir.replace(dir.find("Image-Compressor"),16, "");
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
  double rate;
  int flag = 1;

  PTree tree(png);

  while(flag == 1)
    switch(stoi(adjustment)){
      case 1:
        rate = enterMeasure();
        tree.Prune(rate);
        adjustment = mainMenu();
        break;
      case 2:
        tree.FlipHorizontal();
        adjustment = mainMenu();
        break;
      case 3:
        tree.FlipHorizontal();
        adjustment = mainMenu();
        break;
      case 4:
        flag = 0;
        png = tree.Render();
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
