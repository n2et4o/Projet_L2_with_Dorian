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
    t_move move;
    t_localisation loc;
    int cost;
    struct tree **son;
    int nbson;
}n_node;

n_node* createnode(t_localisation,t_map,t_move, int);

void addson(n_node*,n_node*);

n_node *creattree(t_localisation, t_map);

#endif //TREE_H
