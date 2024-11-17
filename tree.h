//
// Created by Docau on 23/10/2024.
//

#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include "Code_fourni/loc.h"
#include "Code_fourni/map.h"
#include "Code_fourni/moves.h"

typedef struct tree {
    t_localisation loc;
    int cost, *moves;
    struct tree **son;
    int nbson;
}n_node;
/**
 * @brief function to create a node
 * @param loc : the localisation of the robot
 * @param map : map of mars
 * @param int* : robot movements
 * @param int : number of son
 * @return a node
 */
n_node *creat_node (t_localisation , t_map , int *, int );


/**
 * @brief recursive function to create a n-tree
 * @param n_node : the start node
 * @param map : map of mars
 * @param int : depth of the tree
 * @return a n-tree
 */
void creat_tree(n_node*, t_map,int);

/**
 * @brief recursive function to display the tree
 * @param n_node* : the display tree
 * @param int : depth of the tree
 * @param char : prefix
 */
void afficherArbre(n_node* , int , char*);

/**
 * @brief function to find the minimal value in the tree
 * @param n_node* : the tree to look for
 * @return the minimal node
 */
n_node* min_son(n_node*);

/**
 * @brief function free memory
 * @param n_node : tree to free
 */
void free_tree(n_node*)

#endif //TREE_H
