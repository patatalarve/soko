#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"

static int file_size(const char *path) {
    char str[1024];
    int i = 1;
    FILE *file = fopen(path , "r");
    if (file) {
        while (fscanf(file, "%s", str)!= EOF)
            i += 1;
        fclose(file);
    }
    return i;
}

static char **load_map(const char *path) {
    char **tab;
    char str[1024];
    int i = 0;
    FILE * file;
    if ((tab = malloc(sizeof(char *) * file_size(path))) == NULL)
        return NULL;
    file = fopen(path , "r");
    if (file) {
        while (fscanf(file, "%s", str)!= EOF)
            tab[i++] = strdup(str);
        fclose(file);
    }
    tab[i] = NULL;
    return tab;
}

static void find_player(map_s *map) {
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '5' || map->map[i][j] == '6') {
                map->player.y = i;
                map->player.x = j;
                return ;
            }
        }
    }
}

static void find_boxes(map_s *map) {
    int box = 0;
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '2' || map->map[i][j] == '3') {
                box++;
            }
        }
    }
    map->box = malloc(sizeof(coo_s) * box + 1);
    box = 0;
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '2' || map->map[i][j] == '3') {
                map->box[box].x = j;
                map->box[box++].y = i;
            }
        }
    }
    map->box[box].x = -1;
    map->box[box].y = -1;
}

static void find_objectives(map_s *map) {
    int obj = 0;
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '4' || map->map[i][j] == '3') {
                obj++;
            }
        }
    }
    map->obj = malloc(sizeof(coo_s) * obj + 1);
    obj = 0;
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '2' || map->map[i][j] == '3') {
                map->obj[obj].x = j;
                map->obj[obj++].y = i;
            }
        }
    }
    map->obj[obj].x = -1;
    map->obj[obj].y = -1;
}

map_s *create_map(const char *path) {
    map_s *map = malloc(sizeof(map_s));

    if (!map)
        return NULL;
    map->map = load_map(path);
    if (!map->map)
        return NULL;
    find_player(map);
    find_boxes(map);
    find_objectives(map);
    for (int i = 0; map->box[i].x >= 0 || map->obj[i].x >= 0; i++) {
        if ((map->box[i].x >= 0 && !(map->obj[i].x >= 0)) || 
            (map->obj[i].x >= 0 && !(map->box[i].x >= 0)))
            return NULL;
    }
    return map;
}