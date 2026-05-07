#include "game.h"
#include "raylib.h"

t_gridMap   *ft_allocateEmptyGridMap()
{
    t_gridMap   *grid_map;

    grid_map = malloc(sizeof(t_gridMap));
    if (!grid_map)
        return (ft_error("failed to malloc grid_map."));

    grid_map->size_x = 0;
    grid_map->size_y = 0;
    grid_map->nb_tiles = 0;
    grid_map->tile_size = 0;
    grid_map->tilesheet_texture_ptr = NULL;
    grid_map->tiles = NULL;

    return (grid_map);
}

t_gridMap   *ft_initGridMap(t_gridMap *grid_map, int size_x, int size_y, Texture2D *texture_ptr)
{
    int i;

    if (grid_map == NULL)
        return (ft_error("grid_map is NULL for some reason..."));

    grid_map->size_x = size_x;
    grid_map->size_y = size_y;
    grid_map->nb_tiles = size_x * size_y;
    grid_map->tilesheet_texture_ptr = texture_ptr;
    grid_map->tile_size = texture_ptr->height;

    if (grid_map->nb_tiles < 1)
        return (ft_error("size cannot be less than 1."));

    grid_map->tiles = malloc(sizeof(t_gridMapTile) * grid_map->nb_tiles);
    if (grid_map->tiles == NULL)
        return (ft_error("failed to malloc grid_map->tiles."));

    i = 0;
    while (i < grid_map->nb_tiles)
    {
        grid_map->tiles[i].index = 0;
        grid_map->tiles[i].type = TILE_TYPE_EMPTY_GROUND;
        grid_map->tiles[i].texture_ptr = grid_map->tilesheet_texture_ptr;
        grid_map->tiles[i].texture_rec = (Rectangle){
            0, 0,
            grid_map->tilesheet_texture_ptr->height,
            grid_map->tilesheet_texture_ptr->height
        };
        i++;
    }

    return (grid_map);
}

t_gridMap   *ft_createGridMap(int size_x, int size_y, Texture2D *texture_ptr)
{
    t_gridMap   *grid_map;

    grid_map = ft_allocateEmptyGridMap();
    if (grid_map == NULL)
        return (NULL);

    return (ft_initGridMap(grid_map, size_x, size_y, texture_ptr));
}

void        ft_freeGridMap(t_gridMap *grid_map)
{
    if (grid_map == NULL)
        return ;
    if (grid_map->tiles != NULL)
        free(grid_map->tiles);
    free(grid_map);
}

void    ft_gridMapSetTileTextureIndex(t_gridMap *grid_map, int i, int val)
{
    if (grid_map == NULL)
    {
        ft_error("passed NULL to ft_gridMapSetTileTextureIndex.");
        return ;
    }
    if (val < 0 || (val * grid_map->tile_size) > grid_map->tilesheet_texture_ptr->width)
    {
        ft_error("cannot set tile texture index below 0 or above max tilesheet length.");
        return ;
    }

    grid_map->tiles[i].index = val;
    grid_map->tiles[i].texture_rec.x = grid_map->tile_size * val;
}

void    ft_drawGridMap(t_gridMap *grid_map, int off_x, int off_y, float scale)
{
    int i;
    float dest_x;
    float dest_y;

    i = 0;
    while (i < grid_map->nb_tiles)
    {
        dest_x = (float)(i % grid_map->size_x) * ((float)grid_map->tile_size * scale);
        dest_y = (float)((float)((int)(i / grid_map->size_x)) * ((float)grid_map->tile_size * scale));

        dest_x += off_x;
        dest_y += off_y;

        DrawTexturePro(*(grid_map->tilesheet_texture_ptr),
                grid_map->tiles[i].texture_rec,
                (Rectangle){dest_x, dest_y,
                (float)grid_map->tile_size * scale,
                (float)grid_map->tile_size * scale},
                (Vector2){0}, 0.0F, WHITE);
        i++;
    }
}
