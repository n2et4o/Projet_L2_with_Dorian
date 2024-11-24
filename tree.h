//
// Created by Docau on 23/10/2024.
//

#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <string.h>
#include "Code_fourni/loc.h"
#include "Code_fourni/map.h"
#include "Code_fourni/moves.h"

#include <time.h>

// Constantes
#define MAX_TIMERS 4

// Structure pour un chronomètre
typedef struct {
    clock_t start_time;
    double elapsed_time;
    int active;
} Timer;

// Initialise un tableau de chronomètres
void init_timers(Timer* timers);

// Contrôle un chronomètre
// id : identifiant du chronomètre (0 à MAX_TIMERS - 1)
// mode : 0 pour démarrer, 1 pour arrêter
void timer_control(Timer* timers, int id, int mode);

// Affiche les résultats de tous les chronomètres
char* get_timer_result(Timer* timers, int id);

// Réinitialise tous les chronomètres
void reset_timers(Timer* timers);

// Gère le total des temps pour une catégorie donnée (ex : guidage complet)
void add_to_total(Timer* timers, int id, double* total);

// Affiche le total des temps d'une catégorie
void print_total_time(double total);

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
void afficherArbre(n_node* node, int depth, char* prefix, int isLast);

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
void free_tree(n_node*);


#endif //TREE_H
