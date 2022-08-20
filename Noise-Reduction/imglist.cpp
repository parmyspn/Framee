// File:        imglist.cpp
// Date:        2022-01-27 10:21
// Description: Contains partial implementation of ImgList class
//              for CPSC 221 2021W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "imglist.h"

#include <math.h> // provides fmax, fmin, and fabs functions

/**************************
 * MISCELLANEOUS FUNCTIONS *
 **************************/

/*
 * This function is NOT part of the ImgList class,
 * but will be useful for one of the ImgList functions.
 * Returns the "difference" between two hue values.
 * PRE: hue1 is a double between [0,360).
 * PRE: hue2 is a double between [0,360).
 *
 * The hue difference is the absolute difference between two hues,
 * but takes into account differences spanning the 360 value.
 * e.g. Two pixels with hues 90 and 110 differ by 20, but
 *      two pixels with hues 5 and 355 differ by 10.
 */
double HueDiff(double hue1, double hue2)
{
  return fmin(fabs(hue1 - hue2), fabs(360 + fmin(hue1, hue2) - fmax(hue1, hue2)));
}

/*********************
 * CONSTRUCTORS, ETC. *
 *********************/

/*
 * Default constructor. Makes an empty list
 */
ImgList::ImgList()
{
  // set appropriate values for all member attributes here
  northwest = NULL;
  southeast = NULL;
}

/*
 * Creates a list from image data
 * PRE: img has dimensions of at least 1x1
 */
ImgList::ImgList(PNG &img)
{
  // build the linked node structure and set the member attributes appropriately
  unsigned int w = img.width();
  unsigned int h = img.height();
  northwest = connect(img, NULL, NULL, w, h, 0, 0);
}

/*
 * Copy constructor.
 * Creates this this to become a separate copy of the data in otherlist
 */
ImgList::ImgList(const ImgList &otherlist)
{
  // build the linked node structure using otherlist as a template
  Copy(otherlist);
}

/*
 * Assignment operator. Enables statements such as list1 = list2;
 *   where list1 and list2 are both variables of ImgList type.
 * POST: the contents of this list will be a physically separate copy of rhs
 */
ImgList &ImgList::operator=(const ImgList &rhs)
{
  // Re-build any existing structure using rhs as a template

  if (this != &rhs)
  { // if this list and rhs are different lists in memory
    // release all existing heap memory of this list
    Clear();

    // and then rebuild this list using rhs as a template
    Copy(rhs);
  }

  return *this;
}

/*
 * Destructor.
 * Releases any heap memory associated with this list.
 */
ImgList::~ImgList()
{
  // Ensure that any existing heap memory is deallocated
  Clear();
}

/************
 * ACCESSORS *
 ************/

/*
 * Returns the horizontal dimension of this list (counted in nodes)
 * Note that every row will contain the same number of nodes, whether or not
 *   the list has been carved.
 * We expect your solution to take linear time in the number of nodes in the
 *   x dimension.
 */
unsigned int ImgList::GetDimensionX() const
{
  // replace the following line with your implementation

  ImgNode *temp = northwest;
  unsigned int x = 0;
  while (temp != NULL)
  {
    x++;
    temp = temp->east;
  }

  return x;
}

/*
 * Returns the vertical dimension of the list (counted in nodes)
 * It is useful to know/assume that the grid will never have nodes removed
 *   from the first or last columns. The returned value will thus correspond
 *   to the height of the PNG image from which this list was constructed.
 * We expect your solution to take linear time in the number of nodes in the
 *   y dimension.
 */
unsigned int ImgList::GetDimensionY() const
{
  // replace the following line with your implementation
  ImgNode *temp = northwest;
  unsigned int y = 0;
  while (temp != NULL)
  {
    y++;
    temp = temp->south;
  }

  return y;
}

/*
 * Returns the horizontal dimension of the list (counted in original pixels, pre-carving)
 * The returned value will thus correspond to the width of the PNG image from
 *   which this list was constructed.
 * We expect your solution to take linear time in the number of nodes in the
 *   x dimension.
 */
unsigned int ImgList::GetDimensionFullX() const
{
  // replace the following line with your implementation
  ImgNode *temp = northwest;
  unsigned int x = 0;
  while (temp != NULL)
  {
    if (temp->skipright == 0)
      x++;
    else
      x += temp->skipright + 1;
    temp = temp->east;
  }
  return x;
}

/*
 * Returns a pointer to the node which best satisfies the specified selection criteria.
 * The first and last nodes in the row cannot be returned.
 * PRE: rowstart points to a row with at least 3 physical nodes
 * PRE: selectionmode is an integer in the range [0,1]
 * PARAM: rowstart - pointer to the first node in a row
 * PARAM: selectionmode - criterion used for choosing the node to return
 *          0: minimum luminance across row, not including extreme left or right nodes
 *          1: node with minimum total of "hue difference" with its left neighbour and with its right neighbour.
 *        In the (likely) case of multiple candidates that best match the criterion,
 *        the left-most node satisfying the criterion (excluding the row's starting node)
 *        will be returned.
 * A note about "hue difference": For PA1, consider the hue value to be a double in the range [0, 360).
 * That is, a hue value of exactly 360 should be converted to 0.
 * The hue difference is the absolute difference between two hues,
 * but be careful about differences spanning the 360 value.
 * e.g. Two pixels with hues 90 and 110 differ by 20, but
 *      two pixels with hues 5 and 355 differ by 10.
 */
ImgNode *ImgList::SelectNode(ImgNode *rowstart, int selectionmode)
{
  if (rowstart == NULL)
  {
    return NULL;
  }
  // add your implementation below
  if (selectionmode == 0)
  {
    // minimum luminance across row, not including extreme left or right nodes
    ImgNode *temp = rowstart->east;
    ImgNode *result = NULL;
    double val = 10000;
    while (temp->east != NULL)
    {
      if (val > temp->colour.l)
      {
        val = temp->colour.l;
        result = temp;
      }
      temp = temp->east;
    }
    return result;
  }
  else if (selectionmode == 1)
  {
    // node with minimum total of "hue difference" with its left neighbour and with its right neighbour.
    ImgNode *temp = rowstart->east;
    ImgNode *result = temp;
    // The maximum of total differences are 360 (180+180). But for finding minimum, this value must be greater than 360.
    double val = 362;
    while (temp->east != NULL)
    {
      double lhs = HueDiff(temp->west->colour.h, temp->colour.h);
      double rhs = HueDiff(temp->east->colour.h, temp->colour.h);
      if (val > (lhs + rhs))
      {
        val = lhs + rhs;
        result = temp;
      }
      temp = temp->east;
    }
    return result;
  }
  return NULL;
}

/*
 * Renders this list's pixel data to a PNG, with or without filling gaps caused by carving.
 * PRE: fillmode is an integer in the range of [0,2]
 * PARAM: fillgaps - whether or not to fill gaps caused by carving
 *          false: render one pixel per node, ignores fillmode
 *          true: render the full width of the original image,
 *                filling in missing nodes using fillmode
 * PARAM: fillmode - specifies how to fill gaps
 *          0: solid, uses the same colour as the node at the left of the gap
 *          1: solid, using the averaged values (all channels) of the nodes at the left and right of the gap
 *             Note that "average" for hue will use the closer of the angular distances,
 *             e.g. average of 10 and 350 will be 0, instead of 180.
 *             Average of diametric hue values will use the smaller of the two averages
 *             e.g. average of 30 and 210 will be 120, and not 300
 *                  average of 170 and 350 will be 80, and not 260
 *          2: *** OPTIONAL - FOR BONUS ***
 *             linear gradient between the colour (all channels) of the nodes at the left and right of the gap
 *             e.g. a gap of width 1 will be coloured with 1/2 of the difference between the left and right nodes
 *             a gap of width 2 will be coloured with 1/3 and 2/3 of the difference
 *             a gap of width 3 will be coloured with 1/4, 2/4, 3/4 of the difference, etc.
 *             Like fillmode 1, use the smaller difference interval for hue,
 *             and the smaller-valued average for diametric hues
 */
PNG ImgList::Render(bool fillgaps, int fillmode) const
{
  // Add/complete your implementation below

  PNG outpng; // this will be returned later. Might be a good idea to resize it at some point.

  unsigned int w, h;

  if (fillgaps == false)
  {
    w = GetDimensionX();
    h = GetDimensionY();
    outpng.resize(w, h);
    unsigned int x = 0, y = 0;
    ImgNode *temp = northwest;
    ImgNode *row = temp;
    while (temp != NULL)
    {
      row = temp;
      while (row != NULL)
      {
        HSLAPixel *p = outpng.getPixel(y, x);
        *p = row->colour;
        row = row->east;
        y++;
      }
      x++;
      y = 0;
      temp = temp->south;
    }
  }
  else
  {
    w = GetDimensionFullX();
    h = GetDimensionY();
    outpng.resize(w, h);
    if (fillmode == 0)
    {
      unsigned int x = 0, y = 0;
      ImgNode *temp = northwest;
      ImgNode *row = temp;
      while (temp != NULL)
      {
        row = temp;
        while (row != NULL)
        {
          if (row->skipright != 0)
          {
            for (unsigned int i = 0; i <= row->skipright; i++)
            {
              HSLAPixel *p = outpng.getPixel(y, x);
              *p = row->colour;
              y++;
            }
            row = row->east;
          }
          else
          {
            HSLAPixel *p = outpng.getPixel(y, x);
            *p = row->colour;
            row = row->east;
            y++;
          }
        }
        x++;
        y = 0;
        temp = temp->south;
      }
    }
    else if (fillmode == 1)
    {
      unsigned int x = 0, y = 0;
      ImgNode *temp = northwest;
      ImgNode *row = temp;
      while (temp != NULL)
      {
        row = temp;
        while (row != NULL)
        {
          HSLAPixel *p = outpng.getPixel(y, x);
          *p = row->colour;

          y++;
          if (row->skipright != 0)
          {
            ImgNode *end = row->east;
            double h, s, l, a;
            s = (row->colour.s + end->colour.s) / 2;
            a = (row->colour.a + end->colour.a) / 2;
            l = (row->colour.l + end->colour.l) / 2;
            h = (int)((row->colour.h + end->colour.h) / 2) % 180;
            for (unsigned int i = 0; i < row->skipright; i++)
            {
              HSLAPixel *p = outpng.getPixel(y, x);
              p->a = a;
              p->l = l;
              p->h = h;
              p->s = s;
              y++;
            }
          }

          row = row->east;
        }
        x++;
        y = 0;
        temp = temp->south;
      }
    }
  }

  return outpng;
}

/************
 * MODIFIERS *
 ************/

/*
 * Removes exactly one node from each row in this list, according to specified criteria.
 * The first and last nodes in any row cannot be carved.
 * PRE: this list has at least 3 nodes in each row
 * PRE: selectionmode is an integer in the range [0,1]
 * PARAM: selectionmode - see the documentation for the SelectNode function.
 * POST: this list has had one node removed from each row. Neighbours of the created
 *       gaps are linked appropriately, and their skip values are updated to reflect
 *       the size of the gap.
 */
void ImgList::Carve(int selectionmode)
{
  // add your implementation here
  ImgNode *start = northwest;
  while (start != NULL)
  {
    ImgNode *selected = SelectNode(start, selectionmode);
    if (selected != NULL)
    {
      selected->west->skipright++;
      selected->east->skipleft++;
      if (selected->north != NULL)
      {
        selected->north->skipdown++;
        selected->north->south = selected->south;
      }
      if (selected->south != NULL)
      {
        selected->south->skipup++;
        selected->south->north = selected->north;
      }
      selected->west->east = selected->east;
      selected->east->west = selected->west;
      delete selected;
    }
    start = start->south;
  }
}

// note that a node on the boundary will never be selected for removal
/*
 * Removes "rounds" number of nodes (up to a maximum of node width - 2) from each row,
 * based on specific selection criteria.
 * Note that this should remove one node from every row, repeated "rounds" times,
 * and NOT remove "rounds" nodes from one row before processing the next row.
 * PRE: selectionmode is an integer in the range [0,1]
 * PARAM: rounds - number of nodes to remove from each row
 *        If rounds exceeds node width - 2, then remove only node width - 2 nodes from each row.
 *        i.e. Ensure that the final list has at least two nodes in each row.
 * POST: this list has had "rounds" nodes removed from each row. Neighbours of the created
 *       gaps are linked appropriately, and their skip values are updated to reflect
 *       the size of the gap.
 */
void ImgList::Carve(unsigned int rounds, int selectionmode)
{
  // add your implementation here
  for (unsigned int i = 0; i < rounds; i++)
  {
    ImgNode *start = northwest;
    while (start != NULL)
    {
      ImgNode *selected = SelectNode(start, selectionmode);
      if (selected != NULL)
      {
        if (selected->skipleft == 0 && selected->skipright == 0)
        {
          selected->west->skipright++;
          selected->east->skipleft++;
        }
        if (selected->skipleft != 0 && selected->skipright != 0)
        {
          unsigned int m = selected->skipleft > selected->skipright ? selected->skipleft : selected->skipright;
          selected->west->skipright += m;
          selected->east->skipleft += m;
        }
        else if (selected->skipleft != 0)
        {
          selected->west->skipright += selected->skipleft;
          selected->east->skipleft += selected->skipleft;
        }
        else if (selected->skipright != 0)
        {
          selected->west->skipright += selected->skipright;
          selected->east->skipleft += selected->skipright;
        }

        if (selected->north != NULL)
        {
          selected->north->skipdown++;
          selected->north->south = selected->south;
        }
        if (selected->south != NULL)
        {
          selected->south->skipup++;
          selected->south->north = selected->north;
        }
        selected->west->east = selected->east;
        selected->east->west = selected->west;
        delete selected;
      }

      start = start->south;
    }
  }
}

/*
 * Helper function deallocates all heap memory associated with this list,
 * puts this list into an "empty" state. Don't forget to set your member attributes!
 * POST: this list has no currently allocated nor leaking heap memory,
 *       member attributes have values consistent with an empty list.
 */
void ImgList::Clear()
{
  // add your implementation here
  ImgNode *temp = northwest;
  while (temp)
  {
    ImgNode *start = temp->east;
    ImgNode *h = NULL;
    while (start)
    {
      h = start;
      start = start->east;
      delete h;
    }
    h = temp;
    temp = temp->south;
    delete h;
  }
  northwest = NULL;
  southeast = NULL;
}

/* ************************
 *  * OPTIONAL - FOR BONUS *
 ** ************************
 * Helper function copies the contents of otherlist and sets this list's attributes appropriately
 * PRE: this list is empty
 * PARAM: otherlist - list whose contents will be copied
 * POST: this list has contents copied from by physically separate from otherlist
 */
void ImgList::Copy(const ImgList &otherlist)
{
  // add your implementation here
}

/*************************************************************************************************
 * IF YOU DEFINED YOUR OWN PRIVATE FUNCTIONS IN imglist.h, YOU MAY ADD YOUR IMPLEMENTATIONS BELOW *
 *************************************************************************************************/

ImgNode *ImgList::connect(PNG &img, ImgNode *up, ImgNode *left, unsigned int w, unsigned int h, unsigned int x, unsigned int y)
{

  if (x > w - 1 || y > h - 1)
    return NULL;

  ImgNode *temp = new ImgNode();
  temp->colour = *img.getPixel(x, y);
  temp->north = up;
  temp->west = left;
  if (up != NULL && (up->east != NULL) && (up->east->south != NULL))
  {
    // up->east is the north of the temp->east.
    // So up->east->north should be the temp->east
    temp->east = up->east->south;
    temp->east->west = temp;
  }
  else if (up != NULL && (up->east != NULL) && (up->east->south == NULL))
  {
    // NULL is the north of temp->east
    temp->east = connect(img, up, temp, w, h, x + 1, y);
  }
  else
  {
    temp->east = connect(img, NULL, temp, w, h, x + 1, y);
  }

  if (left != NULL && (left->south != NULL) && (left->south->east != NULL))
  {
    // left->south is the west of temp->south
    temp->south = left->south->east;
    temp->south->north = temp;
  }
  else if (left != NULL && (left->south != NULL) && (left->south->east == NULL))
  {
    // NULL is the north of temp->south
    temp->south = connect(img, temp, left->south, w, h, x, y + 1);
  }
  else
  {
    temp->south = connect(img, temp, NULL, w, h, x, y + 1);
  }
  if (x == w - 1 && y == h - 1)
  {
    southeast = temp;
  }

  return temp;
}
