/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
**/

#include "framee.h"
#include "cs221util/PNG.h"
#include <iostream>
#include <filesystem>

using namespace std;


double enterMeasure(string adjustment){
  double measure;
  cout << "Please enter a number between -100 to 100 for " + adjustment << endl;
  cin >> measure;
  return measure;
}

void exitMessage(string message) {
  cout << message << endl;
  exit (EXIT_FAILURE);
}

string mainMenu(){
  string adjustment;
  cout << "Please enter the Filter or Adjustment:\n" << "\t1.Blur\n" <<"\t2.Sharpen\n" <<"\t3.Edge Detection\n" << "\t4.Ridge Detection\n" <<"\t5.Adjust Brightness\n"<< "\t6.Adjust Vibrance\n" <<"\t7.Adjust Warmth\n"<< "\t8.Adjust Brightness Vibrance and Warmth\n" <<"\t9.Export image\n" << endl;
  cin >> adjustment;
  return  adjustment;
}

string getParentDirectory(){
 
  string dir =   __fs::filesystem::current_path();
  dir = dir.replace(dir.find("Image-Filtering"),15, "");
 
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

  double brightness;
  double vibrance;
  double warmth;
  int flag = 1;

  while(flag == 1)
    switch(stoi(adjustment)){
      case 1:
        png = boxBlur(png);
        adjustment = mainMenu();
        break;
      case 2:
        png = sharpen(png);
        adjustment = mainMenu();
        break;
      case 3:
        png = edgeDetect(png);
        adjustment = mainMenu();
        break;
      case 4:
        png = ridgeDetect(png);
        adjustment = mainMenu();
        break;
      case 5:
        brightness = enterMeasure("Brightness");
        png = adjustBrightness(png,brightness);
        adjustment = mainMenu();
        break;
      case 6:
        vibrance = enterMeasure("Vibrance");
        png = adjustVibrance(png,vibrance);
        adjustment = mainMenu();
        break;
      case 7:
        warmth = enterMeasure("Warmth");
        png = adjustWarmth(png,warmth);
        adjustment = mainMenu();
        break;
      case 8:
        brightness = enterMeasure("Brightness");
        vibrance = enterMeasure("Vibrance");
        warmth = enterMeasure("Warmth");
        png = adjustBrightnessVibranceWarmth(png,brightness, vibrance, warmth);
        adjustment = mainMenu();
        break;
      case 9:
        flag = 0;
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
