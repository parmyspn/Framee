/*
 *  File:        ptree-private.h
 *  Description: Private functions for the PTree class
 *  Date:        2022-03-06 03:30
 *
 *               DECLARE YOUR PTREE PRIVATE MEMBER FUNCTIONS HERE
 */

#ifndef _PTREE_PRIVATE_H_
#define _PTREE_PRIVATE_H_



// Remove all nodes from binary tree
void remove_all(Node *ptr);

// Add all nodes from the other tree into the empty tree
Node *add_recursive(Node *my_root, Node *other_root);

HSLAPixel get_pixel_avg(PNG &im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h);

int get_size(Node *root) const;

int get_leaves(Node *root) const;

void render_helper(PNG &img, Node *root) const;

void horizonntal_helper(Node *node) const;

void vertical_helper(Node *node) const;

void prune_helper(Node *node, double &tolerance);

int leaves_count_tolerance(Node* curent, Node* sub_root, double &tolerance);
#endif
