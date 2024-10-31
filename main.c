#include <stdio.h>
#include "Code_fourni/map.h"
#include "Code_fourni/loc.h"
#include "Code_fourni/moves.h"
#include "tree.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);


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

    t_localisation marc = loc_init(6,5,0), test = loc_init(0,0,0);
    printf("%d\n",map.costs[marc.pos.x][marc.pos.y]);
    //test = move(marc, 2);
    //printf("[%d][%d][%d]",test.pos.x,test.pos.y,test.ori);
    n_node *tree =  creattree(marc,map);
    printf("-------------------->%d", tree->son[1]->cost);
    return 0;
}
