#include <stdio.h>
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


    //displayMap(map);
    printf("\nDorian's part\n");
    t_localisation marc = loc_init(4,5,0), test = loc_init(0,0,0);
    printf("%d\n",map.costs[marc.pos.x][marc.pos.y]);
    //marc = move(marc, 2);
    printf("\n\n[%d][%d][%d]\n\n",test.pos.x,test.pos.y,test.ori);
    n_node *tree =  creattree(marc,map);
    printf("-------------------->%d", tree->son[1]->cost);

    if (tree->son[1]->cost > 10000 || tree->son[1]->cost < 0){
        printf("\nSortie de la carte");
    }

    run_rover(plateau,marc,map);

    return 0;
}
