
#ifndef _PTREE_H_
#define _PTREE_H_

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace std;
using namespace cs221util;

class Node {
  public:
    
    pair<unsigned int, unsigned int> upperleft; 
    unsigned int width;  
    unsigned int height; 
    HSLAPixel avg;       
    Node* A;             
    Node* B;             

  
    Node(pair<unsigned int, unsigned int> ul = make_pair(0, 0), unsigned int w = 0, unsigned int h = 0, HSLAPixel avgc = HSLAPixel(0, 0, 0), Node* childA = nullptr, Node* childB = nullptr) : upperleft(ul), width(w), height(h), avg(avgc), A(childA), B(childB) {}
};


class PTree {


  private:

    Node* root; 



    void Clear();

   
    void Copy(const PTree& other);

    Node* BuildNode(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h);




  public:

    PTree(PNG& im);

   
    PTree(const PTree& other);

   
    PTree& operator=(const PTree& other);

    
    ~PTree();

   
    PNG Render() const;

    
    void Prune(double tolerance);

    
    int Size() const;

    
    int NumLeaves() const;

    
    void FlipHorizontal();

    void FlipVertical();

    
    Node* GetRoot();

  private:
    
    #include "ptree-private.h"
};

#endif
