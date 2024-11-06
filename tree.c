//
// Created by Docau on 23/10/2024.
//
#include <stdio.h>
#include"tree.h"
n_node* creatnode(t_localisation loc,t_map map,t_move move)
{
    n_node *newnode = (n_node*)malloc(sizeof(n_node));
    newnode->loc = loc;
    newnode->cost = map.costs[newnode->loc.pos.x][newnode->loc.pos.y];
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
    for(int i = 0; i < 5; i++){ // la profondeur de l'arbre

        //printf("%d\n",j);
        switch (i) {
            case 0:
                for(t_move j = 0 ; j < 7; j++) {
                    printf("%d\n",j);
                    t_localisation new = move(marc, j);
                    //printf("[%d][%d][%d]\n", new.pos.y, new.pos.x, new.ori);
                    n_node *son = creatnode(new, map, j);
                    addson(tree, son);
                }
                break;
            case 1:
                for(t_move j = 0 ; j < 7; j++) {

                    t_localisation new = tree->son[0]->loc;
                    //printf("[%d][%d][%d]\n", new.pos.y, new.pos.x, new.ori);
                    n_node *son = creatnode(new, map, j);
                    addson(tree->son[0], son);
                }
                printf("\n");
                break;
            case 2:
                printf("\n");
                break;
            case 3:
                printf("\n");
                break;
            case 4:
                printf("\n");
                break;
            default:
        }
    }


    return tree;
}