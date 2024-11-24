#include <stdio.h>
#include "Code_fourni/map.h"
#include "Code_fourni/loc.h"
#include "Code_fourni/moves.h"
#include "tree.h"
#include "interfaces_graphiques.h"

int main(int argc, char *argv[]) {

    Timer timers[MAX_TIMERS];
    init_timers(timers);

    // Variable pour accumuler le temps total du guidage complet
    double total_guidage_complet = 0;

    t_map map = createMapFromFile("..\\maps\\example1.map");
    //t_map map = createTrainingMap();

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    int plateau[map.y_max][map.x_max];

    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
            plateau[i][j] = map.soils[i][j];
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
            //plateau[i][j] = map.costs[i][j];
        }
        printf("\n");
    }
    // Chronomètre du guidage complet (Phase)
    timer_control(timers, 3, 0); // Démarre le guidage complet

    t_localisation marc = loc_init(4,4,0);
    int T[] = {0,1,2,3,4,5,6};
    n_node *tree = creat_node(marc,map,T,7);

    timer_control(timers, 0, 0);
    creat_tree(tree,map,0);
    timer_control(timers, 0, 1);

    printf("\n");
    afficherArbre(tree,0,"",1);
    printf("--->ICI");

    timer_control(timers, 1, 0);
    min_son(tree);
    timer_control(timers, 1, 1);

    timer_control(timers, 3, 1);
    // Récupérer les résultats des chronomètres sous forme de chaînes de caractères
    char* result_0 = get_timer_result(timers, 0); // Résultat du chronomètre 0
    char* result_1 = get_timer_result(timers, 1); // Résultat du chronomètre 1
    char* result_3 = get_timer_result(timers, 3); // Résultat du chronomètre 3

    const char* complex[MAX_TIMERS] = {
            result_3,
            result_1,
            result_0,
    };

    run_rover(plateau, marc, map,tree,complex);

    return 0;
}
