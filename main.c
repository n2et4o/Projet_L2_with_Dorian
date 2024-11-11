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

    int T[] = {0,1,2,3,4,5,6};
    t_localisation marc = loc_init(6,5,0);
    n_node *tree = creat_node(marc,map,T,7);
    creat_tree(tree,map,0);
    printf("\nla");
    //printf("----------------------->%d",tree->son[0]->cost);


    return 0;
}
