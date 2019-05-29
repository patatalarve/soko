
#include <stdio.h>

#include "map.h"

int main() {
    map_s *map = create_map("./level/map.dat");

    if (!map)
        return 1;

    return 0;
}