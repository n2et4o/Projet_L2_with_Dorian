#include <stdio.h>
#include "Code_fourni/map.h"
#include "Code_fourni/loc.h"
#include "Code_fourni/moves.h"
#include "tree.h"
#include "interfaces_graphiques.h"

int main(int argc, char *argv[]) {

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

    t_localisation marc = loc_init(4,4,0);
    int T[] = {0,1,2,3,4,5,6};
    n_node *tree = creat_node(marc,map,T,7);
    creat_tree(tree,map,0);
    printf("\n");
    afficherArbre(tree,0,"",1);
    printf("--->ICI");
    run_rover(plateau, marc, map,tree);

    //free_tree(tree);

    return 0;
}
