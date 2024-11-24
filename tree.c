//
// Created by Docau on 23/10/2024.
//
#include <stdio.h>
#include"tree.h"


// Description des chronomètres
const char* timer_descriptions[MAX_TIMERS] = {
        "Construction de l'arbre",
        "Recherche de la feuille minimale",
        "Calcul du chemin vers la feuille",
        "Guidage complet de MARC"
};

// Initialise les chronomètres
void init_timers(Timer* timers) {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timers[i].elapsed_time = 0;
        timers[i].active = 0;
    }
}

// Contrôle un chronomètre
void timer_control(Timer* timers, int id, int mode) {
    if (id < 0 || id >= MAX_TIMERS) {
        printf("ID de chronomètre invalide : %d\n", id);
        return;
    }

    Timer* timer = &timers[id];
    if (mode == 0) { // Démarrer
        if (timer->active) return; // Si déjà actif, ne rien faire
        timer->start_time = clock();
        timer->active = 1;
    } else if (mode == 1) { // Arrêter
        if (!timer->active) return; // Si déjà arrêté, ne rien faire
        clock_t end_time = clock();
        timer->elapsed_time += (double)(end_time - timer->start_time) / CLOCKS_PER_SEC;
        timer->active = 0;
    }
}

// Affiche les résultats des chronomètres

// Affiche les résultats d'un chronomètre sous forme de chaîne de caractères
char* get_timer_result(Timer* timers, int id) {
    // Vérifier si l'ID est valide
    if (id < 0 || id >= MAX_TIMERS) {
        return "ID de chronomètre invalide.";
    }

    // Allouer une chaîne de caractères pour le résultat
    char* result = (char*)malloc(256 * sizeof(char)); // Suffisant pour le format du résultat

    // Formater le résultat dans la chaîne
    snprintf(result, 256, "%s : %.6f s", timer_descriptions[id], timers[id].elapsed_time);

    return result; // Retourner la chaîne contenant le résultat
}

// Réinitialise tous les chronomètres
void reset_timers(Timer* timers) {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timers[i].elapsed_time = 0;
        timers[i].start_time = 0;
        timers[i].active = 0;
    }
    printf("Chronomètres réinitialisés.\n");
}

// Ajoute le temps d'un chronomètre à un total
void add_to_total(Timer* timers, int id, double* total) {
    *total += timers[id].elapsed_time;
}

// Affiche le total des temps d'une catégorie
void print_total_time(double total) {
    printf("Temps total : %.6f secondes\n", total);
}

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

void afficherArbre(n_node* node, int depth, char* prefix, int isLast) {
    if (node == NULL || depth == 5 || node->cost > 11111) {
        return;
    }

    // Afficher le nœud actuel
    printf("%s%s- Cout: %d\n", prefix, isLast ? "└──" : "├──", node->cost);

    // Mettre à jour le préfixe pour les fils
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "   " : "│  ");

    for (int i = 0; i < node->nbson; i++) {
        afficherArbre(node->son[i], depth + 1, newPrefix, i == node->nbson - 1);
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

