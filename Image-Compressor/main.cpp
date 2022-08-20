/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
**/

#include "framee.h"
#include "cs221util/PNG.h"


int main() {

  cs221util::PNG png, png2, result;



  
  png.readFromFile("originals/kkkk-256x224.png");

  // call the tree constructor
  PTree tree(png);

  // pruning tree
  tree.Prune(0.05);
  int treesize = tree.Size();
  int treenumleaves = tree.NumLeaves();



  result = tree.Render();

  result.writeToFile("images/prune-kkkk-tol005.png");
  
  return 0;
}