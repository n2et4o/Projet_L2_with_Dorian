//
// Created by Docau on 23/10/2024.
//
#include <stdio.h>
#include"tree.h"
static int* suppTabval(int* T, int index, int size) {

    int* newT = (int*)malloc((size - 1) * sizeof(int));

    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            newT[j++] = T[i];
        }
    }

    return newT;
}

n_node *creat_node (t_localisation loc, t_map map, int *mouves, int nbmouv)
{
    n_node *node = (n_node*) malloc(sizeof(n_node));
    node->loc = loc;
    node->cost = ((loc.pos.y > map.x_max || loc.pos.y < -1) || (loc.pos.x > map.y_max || loc.pos.x < -1))? 1000 : map.costs[node->loc.pos.x][node->loc.pos.y];
    node->moves = mouves;
    node->nbson = nbmouv;
    node->son = (n_node**) malloc(node->nbson*sizeof (n_node*));
    return node;
}


void creat_tree(n_node *tree, t_map map, int depth)
{
    if (depth >= 5) {
        return;
    }
    int *newmove = NULL;
    n_node *node = NULL;
    t_localisation newloc;
    printf("-[%d]-\n",tree->cost);
    for (int i = 0; i < tree->nbson; i++) {
        newmove = suppTabval(tree->moves, i, tree->nbson);
        newloc = move(tree->loc, i);
        //printf("[%d][%d][%d]\n",newloc.pos.x,newloc.pos.y,newloc.ori);
        node = creat_node(newloc, map, newmove, tree->nbson - 1);
        tree->son[i] = node;
        creat_tree(tree->son[i], map,depth+1);
        free(newmove);
    }
}
