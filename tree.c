//
// Created by Docau on 23/10/2024.
//
#include <stdio.h>
#include"tree.h"

//definition des fonction local
static int loc_ok(t_position loc, t_map map){
    return (loc.x >= 0 && loc.x < map.y_max && loc.y >= 0 && loc.y < map.x_max );
}

static n_node* find_min_son(n_node *node, n_node **min_node, int *cost_min, int depth)
{
    if (node == NULL || depth >= 5 || node->cost >= 10000) {
        return *min_node;
    }


    if (node->cost < *cost_min){
        *cost_min = node->cost;
        *min_node = node;
    }
    for (int i = 0; i < node->nbson; i++){
        find_min_son(node->son[i],&*min_node, cost_min,depth+1);
    }

    return *min_node;
}

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
    node->cost = (loc_ok(loc.pos,map) == 0)? 11112 : map.costs[node->loc.pos.x][node->loc.pos.y];
    node->moves = mouves;
    node->nbson = nbmouv;
    node->son = (n_node**) malloc(node->nbson*sizeof (n_node*));
    return node;
}


void creat_tree(n_node *tree, t_map map, int depth)
{
    if (depth >= 5 || tree->cost > 11111) {
        return;
    }
    int *newmove = NULL;
    n_node *node = NULL;
    t_localisation newloc;
    for (int i = 0; i < tree->nbson; i++) {
        newmove = suppTabval(tree->moves, i, tree->nbson);
        newloc = move(tree->loc, i);
        node = creat_node(newloc, map, newmove, tree->nbson - 1);
        tree->son[i] = node;
        creat_tree(tree->son[i], map,depth + 1);
        free(newmove);
    }
}

void afficherArbre(n_node* node, int depth, char* prefix)
{
    if (node == NULL || depth == 5 || node->cost > 11111) {
        return;
    }

    printf("%s|- Cout: %d\n", prefix, node->cost);

    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s|  ", prefix);

    for (int i = 0; i < node->nbson; i++) {
        afficherArbre(node->son[i], depth + 1, newPrefix);
    }
}

n_node* min_son(n_node *tree)
{
    n_node *stok = NULL;
    int min = 10000;

    return find_min_son(tree, &stok, &min,0);

}

void free_tree(n_node* node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < node->nbson; i++) {
        free_tree(node->son[i]);
    }
    free(node->son);
    free(node->moves);
    free(node);
}

