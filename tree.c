//
// Created by Docau on 23/10/2024.
//
#include <stdio.h>
#include"tree.h"
n_node* creatnode(t_localisation pos,t_map map,t_move move)
{
    t_position npos = pos.pos;
    n_node *newnode = (n_node*)malloc(sizeof(n_node));
    newnode->cost = map.costs[npos.x][npos.y];
    newnode->move = move;
    newnode->nbson = 0;
    newnode->son = (n_node**) malloc(sizeof(n_node*));
    return newnode;
}

void addson(n_node *parents,n_node *son)
{
    parents->son[parents->nbson] = son;
    parents->nbson++;
}

n_node *creattree(t_localisation marc, t_map map)
{
    n_node *tree = creatnode(marc,map,-1);
    //for(int i = 0; i < 5; i++){ // la profondeur de l'arbre
    for(int j = 0 ; j < 7; j++){
        //printf("%d\n",j);
        t_localisation new = move(marc,j);
        printf("[%d][%d][%d]\n",new.pos.y,new.pos.x,new.ori);
        n_node *son = creatnode(new,map,j);
            addson(tree , son);
        }
    //}


    return tree;
}