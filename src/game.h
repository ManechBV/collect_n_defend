#ifndef GAME_H
# define GAME_H

# include "raylib.h"
# include "raymath.h"
# include <stdlib.h>
# include <stdio.h>

//  errorMsg.c
void    *ft_error(char *msg);
int    ft_errorInt(char *msg, int ret);

//  entityBuffer.c
enum    e_entityDataType
{
    ENTITY_DATA_TYPE_NULL,
    ENTITY_DATA_TYPE_BASIC,
    ENTITY_DATA_TYPE_GRID_MAP
};

typedef struct  s_entity
{
    void                    *data;
    enum e_entityDataType   data_type;
    void                    (*ftptr_drawEntityMethod)(int i);
    void                    (*ftptr_freeEntityMethod)(int i);
    struct s_entity         *next;
    struct s_entity         *prev;
}   t_entity;

typedef struct  s_entityBuffer
{
    t_entity    *entity_chain_head;
    t_entity    **entity_ptr_array;
    int         count;
}   t_entityBuffer;

extern t_entityBuffer   *G_entity_buffer;

t_entity    *ft_createEmptyEntityChain();
int         ft_initEntityBuffer();
t_entity    *ft_entityBufferPush(t_entity *entity);
void        ft_drawEntityBuffer();
void        ft_freeEntityBuffer();

//  gridMap.c
enum    e_tileType
{
    TILE_TYPE_EMPTY_GROUND,
    TILE_TYPE_ENERGY_SOURCE,
    TILE_TYPE_ENEMY_SPAWNER
};

typedef struct  s_gridMapTile
{
    Texture2D       *texture_ptr;
    Rectangle       texture_rec;
    int             index;
    enum e_tileType type;
}   t_gridMapTile;

typedef struct  s_gridMap
{
    Texture2D       *tilesheet_texture_ptr;
    int             size_x;
    int             size_y;
    int             nb_tiles;
    int             tile_size;
    t_gridMapTile   *tiles;
}   t_gridMap;

t_gridMap   *ft_allocateEmptyGridMap();
t_gridMap   *ft_initGridMap(t_gridMap *grid_map, int size_x, int size_y, Texture2D *texture_ptr);
t_gridMap   *ft_createGridMap(int size_x, int size_y, Texture2D *texture_ptr);
void        ft_drawGridMap(t_gridMap *grid_map, int off_x, int off_y, float scale);
void        ft_freeGridMap(t_gridMap *grid_map);
void        ft_gridMapSetTileTextureIndex(t_gridMap *grid_map, int i, int val);
t_entity    *ft_entityCreateGridMap(int size_x, int size_y, Texture2D *texture_ptr);
void        ft_entityDrawGridMap(int i);
void        ft_entityFreeDataGridMap(int i);

#endif
