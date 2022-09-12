

#include "ptree.h"
#include "hue_utils.h" 

using namespace cs221util;
using namespace std;


typedef pair<unsigned int, unsigned int> pairUI;



void PTree::Clear()
{
  remove_all(root);
}


void PTree::Copy(const PTree &other)
{
  root = add_recursive(root, other.root);
}


Node *PTree::BuildNode(PNG &im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h)
{


  if (w == 0 || h == 0)
  {
    return nullptr;
  }

  Node *result = new Node();
  // Average the pixels
  result->avg = get_pixel_avg(im, ul, w, h);
  result->height = h;
  result->width = w;
  result->upperleft = ul;

  if (w < h)
  {
    if (h % 2 == 0 || h == 1)
    {
      result->A = BuildNode(im, make_pair(ul.first, ul.second), w, h / 2);
      result->B = BuildNode(im, make_pair(ul.first, ul.second + h / 2), w, h / 2);
    }
    else
    {
      result->A = BuildNode(im, make_pair(ul.first, ul.second), w, h / 2);
      result->B = BuildNode(im, make_pair(ul.first, ul.second + (h / 2)), w, (h / 2) + 1);
    }
  }
  else
  {
    if (w % 2 == 0 || w == 1)
    {
      result->A = BuildNode(im, make_pair(ul.first, ul.second), w / 2, h);
      result->B = BuildNode(im, make_pair(ul.first + w / 2, ul.second), (w / 2), h);
    }
    else
    {
      result->A = BuildNode(im, make_pair(ul.first, ul.second), w / 2, h);
      result->B = BuildNode(im, make_pair(ul.first + w / 2, ul.second), (w / 2) + 1, h);
    }
  }

  return result;
}




/*
 *  Constructor that builds the PTree using the provided PNG.
 *
 *  PARAM: im - reference image which will provide pixel data for the constructed tree's leaves
 *  POST:  The newly constructed tree contains the PNG's pixel data in each leaf node.
 */
PTree::PTree(PNG &im)
{
  // add your implementation below
  root = BuildNode(im, make_pair(0, 0), im.width(), im.height());
}

/*
 *  Copy constructor
 *  Builds a new tree as a copy of another tree.
 *
 *  PARAM: other - an existing PTree to be copied
 *  POST:  This tree is constructed as a physically separate copy of other tree.
 */
PTree::PTree(const PTree &other)
{
  
  Copy(other);
}

/*
 *  Assignment operator
 *  Rebuilds this tree as a copy of another tree.
 *
 *  PARAM: other - an existing PTree to be copied
 *  POST:  If other is a physically different tree in memory, all pre-existing dynamic
 *           memory in this tree is deallocated and this tree is reconstructed as a
 *           physically separate copy of other tree.
 *         Otherwise, there is no change to this tree.
 */
PTree &PTree::operator=(const PTree &other)
{
  // add your implementation below
  Copy(other);

  return *this;
}

/*
 *  Destructor
 *  Deallocates all dynamic memory associated with the tree and destroys this PTree object.
 */
PTree::~PTree()
{
  // add your implementation below
  Clear();
}

/*
 *  Traverses the tree and puts the leaf nodes' color data into the nodes'
 *  defined image regions on the output PNG.
 *  For non-pruned trees, each leaf node corresponds to a single pixel that will be coloured.
 *  For pruned trees, each leaf node may cover a larger rectangular region that will be
 *  entirely coloured using the node's average colour attribute.
 *
 *  You may want to add a recursive helper function for this!
 *
 *  RETURN: A PNG image of appropriate dimensions and coloured using the tree's leaf node colour data
 */
PNG PTree::Render() const
{

  PNG im;
  im.resize(root->width, root->height);
  render_helper(im, root);
  return im;
}

/*
 *  Trims subtrees as high as possible in the tree. A subtree is pruned
 *  (its children are cleared/deallocated) if ALL of its leaves have colour
 *  within tolerance of the subtree root's average colour.
 *  Pruning criteria should be evaluated on the original tree, and never on a pruned
 *  tree (i.e. we expect that Prune would be called on any tree at most once).
 *  When processing a subtree, you should determine if the subtree should be pruned,
 *  and prune it if possible before determining if it has subtrees that can be pruned.
 *
 *
 *  PRE:  This tree has not been previously pruned (and is not copied/assigned from a tree that has been pruned)
 *  POST: Any subtrees (as close to the root as possible) whose leaves all have colour
 *        within tolerance from the subtree's root colour will have their children deallocated;
 *        Each pruned subtree's root becomes a leaf node.
 */
void PTree::Prune(double tolerance)
{
 
  prune_helper(root, tolerance);
}

/*
 *  Returns the total number of nodes in the tree.
 *  This function should run in time linearly proportional to the size of the tree.
 *
 *  You may want to add a recursive helper function for this!
 */
int PTree::Size() const
{
  // replace the line below with your implementation
  return get_size(root);
}

/*
 *  Returns the total number of leaf nodes in the tree.
 *  This function should run in time linearly proportional to the size of the tree.
 *
 *  You may want to add a recursive helper function for this!
 */
int PTree::NumLeaves() const
{
  // replace the line below with your implementation
  return get_leaves(root);
}

/*
 *  Rearranges the nodes in the tree, such that a rendered PNG will be flipped horizontally
 *  (i.e. mirrored over a vertical axis).
 *  This function runs in time linearly proportional to the size of the tree.
 *
 *  You may want to add a recursive helper function for this!
 *
 *  POST: Tree has been modified so that a rendered PNG will be flipped horizontally.
 */
void PTree::FlipHorizontal()
{
 
  horizonntal_helper(root);
}

/*
 *  Like the function above, rearranges the nodes in the tree, such that a rendered PNG
 *  will be flipped vertically (i.e. mirrored over a horizontal axis).
 *  This function should runs in time linearly proportional to the size of the tree.
 *
 *  You may want to add a recursive helper function for this!
 *
 *  POST: Tree has been modified so that a rendered PNG will be flipped vertically.
 */
void PTree::FlipVertical()
{
  vertical_helper(root);
}

/*
 *  Provides access to the root of the tree.
 *  This is only used for testing.
 */
Node *PTree::GetRoot()
{
  return root;
}



void PTree::remove_all(Node *ptr)
{
  if (ptr)
  {
    remove_all(ptr->A);
    remove_all(ptr->B);
    delete ptr;
    ptr = nullptr;
  }
}

Node *PTree::add_recursive(Node *my_root, Node *other_root)
{
  if (other_root)
  {
    my_root = new Node(other_root->upperleft, other_root->width, other_root->height, other_root->avg);
    my_root->A = add_recursive(my_root->A, other_root->A);
    my_root->B = add_recursive(my_root->B, other_root->B);
    return my_root;
  }
  return nullptr;
}

HSLAPixel PTree::get_pixel_avg(PNG &im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h)
{
  unsigned int count = h * w;

  double l = 0;
  double a = 0;
  double s = 0;
  double hu = 0;

  double x = 0;
  double y = 0;
  for (unsigned int i = ul.first; i < w + ul.first; i++)
  {
    for (unsigned int j = ul.second; j < h + ul.second; j++)
    {
      HSLAPixel *p = im.getPixel(i, j);
      a += p->a;
      s += p->s;
      l += p->l;
      x += Deg2X(p->h);
      y += Deg2Y(p->h);
    }
  }
  a /= count;
  s /= count;
  l /= count;
  x /= count;
  y /= count;
  hu = XY2Deg(x, y);
  HSLAPixel *pix_candidate = new HSLAPixel(hu, s, l, a);
  return *pix_candidate;
}

int PTree::get_size(Node *root) const
{
  if (root == nullptr)
    return 0;
  return get_size(root->A) + get_size(root->B) + 1;
}

int PTree::get_leaves(Node *root) const
{
  if (root == nullptr)
    return 0;
  if (root->A == nullptr && root->B == nullptr)
    return 1;
  return get_leaves(root->A) + get_leaves(root->B);
}

void PTree::render_helper(PNG &img, Node *root) const
{

  if (root == nullptr)
  {
    return;
  }
  // Render leaf
  if (root->A == nullptr && root->B == nullptr)
  {
    for (unsigned int i = root->upperleft.first; i < root->width + root->upperleft.first; i++)
    {
      for (unsigned int j = root->upperleft.second; j < root->height + root->upperleft.second; j++)
      {
        HSLAPixel *p = img.getPixel(i, j);
        p->a = root->avg.a;
        p->l = root->avg.l;
        p->h = root->avg.h;
        p->s = root->avg.s;
      }
    }
  }
  render_helper(img, root->A);
  render_helper(img, root->B);
}

void PTree::horizonntal_helper(Node *node) const
{
  if (node->A == nullptr && node->B == nullptr)
    return;

  if (node->width >= node->height)
  {
    node->B->upperleft = make_pair(node->upperleft.first, node->upperleft.second);
    node->A->upperleft = make_pair(node->upperleft.first + node->B->width, node->upperleft.second);
  }
  else
  {
    node->A->upperleft = make_pair(node->upperleft.first, node->upperleft.second);
    node->B->upperleft = make_pair(node->upperleft.first, node->upperleft.second + node->height / 2);
  }

  horizonntal_helper(node->B);
  horizonntal_helper(node->A);
}

void PTree::vertical_helper(Node *node) const
{
  if (node->A == nullptr && node->B == nullptr)
    return;

  if (node->width < node->height)
  {
    node->B->upperleft = make_pair(node->upperleft.first, node->upperleft.second);
    node->A->upperleft = make_pair(node->upperleft.first, node->upperleft.second + node->B->height);
  }
  else
  {
    node->A->upperleft = make_pair(node->upperleft.first, node->upperleft.second);
    node->B->upperleft = make_pair(node->upperleft.first + node->width / 2, node->upperleft.second);
  }

  vertical_helper(node->A);
  vertical_helper(node->B);
}

void PTree::prune_helper(Node *node, double &tolerance)
{
  if (node == nullptr || (node->A == nullptr || node->B == nullptr))
    return;
  int total = get_leaves(node);
  int sub = leaves_count_tolerance(node, node, tolerance);
  if (sub == total)
  {
    remove_all(node->A);
    remove_all(node->B);
    node->A = nullptr;
    node->B = nullptr;
  }
  prune_helper(node->B, tolerance);
  prune_helper(node->A, tolerance);
}

int PTree::leaves_count_tolerance(Node *current, Node *sub_root, double &tolerance)
{
  if (current == nullptr)
    return 0;
  if (current->A == nullptr || current->B == nullptr)
  {
    if (sub_root->avg.dist(current->avg) <= tolerance)
    {
      return 1;
    }
    return 0;
  }
  return leaves_count_tolerance(current->A, sub_root, tolerance) +
         leaves_count_tolerance(current->B, sub_root, tolerance);
}
