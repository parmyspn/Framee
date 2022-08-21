/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "framee.h"
#include "cs221util/PNG.h"


int main() {
  cs221util::PNG png, png2, result;

  png.readFromFile("rosegarden.png");
  result = adjustWarmth(png, 100);
  result.writeToFile("out-warmth.png");


  png.readFromFile("rosegarden.png");
  result = adjustBrightness(png, 50);
  result.writeToFile("out-brightness.png");

  png.readFromFile("rosegarden.png");
  result = adjustVibrance(png, 50);
  result.writeToFile("out-vibrance.png");


  png.readFromFile("rosegarden.png");
  result = grayscale(png);
  result.writeToFile("out-grayscale.png");

  png.readFromFile("dog.png");
  result = edgeDetect(png);
  result.writeToFile("out-edgeDetect.png");

  png.readFromFile("rosegarden.png");
  result = ridgeDetect(png);
  result.writeToFile("out-ridgeDetect.png");

  png.readFromFile("rosegarden.png");
  result = boxBlur(png);
  result.writeToFile("out-boxblur.png");
  
  png.readFromFile("rosegarden.png");
  result = sharpen(png);
  result.writeToFile("out-sharpen.png");
  


  png2.readFromFile("overlay.png");
  result = watermark(png, png2);
  result.writeToFile("out-watermark.png");
  
  return 0;
}
