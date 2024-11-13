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
n_node *creat_node (t_localisation , t_map , int *, int );
void creat_tree(n_node*, t_map,int);
void print_tree(n_node *node, int depth);

#endif //TREE_H