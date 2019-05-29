
#ifndef MAP_H_
# define MAP_H_

typedef struct  coo_t {
    int x;
    int y;
}               coo_s;

typedef struct  map_t {
    coo_s player;
    char **map;
    coo_s *box;
    coo_s *obj;
}               map_s;

map_s *create_map(const char* path);

#endif