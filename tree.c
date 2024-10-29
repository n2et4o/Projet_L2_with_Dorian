//
// Created by Docau on 23/10/2024.
//
#include"tree.h"
n_node* creatnode(t_localisation marc,t_map map)
{
    int x = marc.pos.x , y = marc.pos.y;
    n_node *newnode = (n_node*)malloc(sizeof(n_node));
    newnode->val = map.costs[x][y];
    newnode->nbson = 0;
    return newnode;
}

void addson(n_node *son,n_node *parents)
{
    parents->son = son;
    return;
}