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
    int val;
    struct tree **son;
    int nbson;
}n_node;

n_node* createnode(t_localisation,t_map);

void addson(n_node*,n_node*);



#endif //TREE_H
