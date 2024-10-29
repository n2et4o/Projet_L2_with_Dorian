#include <stdio.h>
#include "Code_fourni/map.h"
#include "Code_fourni/loc.h"
#include "Code_fourni/moves.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    t_localisation Marc = loc_init(5, 5, NORTH);
    printf("[%d][%d][%d]\n",Marc.pos.x,Marc.pos.y,Marc.ori);
    Marc = move(Marc,T_RIGHT);
    Marc = move(Marc,T_RIGHT);
    printf("after mouv [%d][%d][%d]\n",Marc.pos.x,Marc.pos.y,Marc.ori);
    /*
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    */
    printf("-------------------->%d", map.costs[3][2]);
    return 0;
}
