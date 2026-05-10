#include "game.h"
#include "raylib.h"

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
    struct s_entity         *next;
    struct s_entity         *prev;
}   t_entity;

typedef struct  s_entityBuffer
{
    t_entity    *entity_chain_head;
    t_entity    **entity_ptr_array;
    int         count;
}   t_entityBuffer;

static t_entityBuffer   *G_entity_buffer = NULL;

t_entity    *ft_createEmptyEntityChain();
int         ft_initEntityBuffer();
int         ft_entityBufferPush(t_entity *entity);
void        ft_drawEntityBuffer();

int         ft_entityCreateGridMap(int size_x, int size_y, Texture2D *texture_ptr);
void        ft_entityDrawGridMap(int i);


t_entity    *ft_createEmptyEntityChain()
{
    t_entity    *entity_head;

    entity_head = malloc(sizeof(t_entity));
    if (!entity_head)
        return (ft_error("failed to malloc entity."));

    entity_head->data = NULL;
    entity_head->data_type = ENTITY_DATA_TYPE_NULL;
    entity_head->ftptr_drawEntityMethod = NULL;
    entity_head->next = NULL;
    entity_head->prev = NULL;

    return (entity_head);
}

int ft_initEntityBuffer()
{
    t_entity    *entity_chain;

    G_entity_buffer = malloc(sizeof(t_entityBuffer));
    if (!G_entity_buffer)
        return (-1);

    G_entity_buffer->count = 0;
    G_entity_buffer->entity_ptr_array = NULL;

    G_entity_buffer->entity_chain_head = ft_createEmptyEntityChain();
    if (G_entity_buffer->entity_chain_head == NULL)
        return (-1);

    G_entity_buffer->entity_ptr_array = malloc(sizeof(t_entity*) * (G_entity_buffer->count + 1));
    if (G_entity_buffer->entity_ptr_array == NULL)
        return (ft_errorInt("failed to malloc ptr entity array.", -1));

    G_entity_buffer->entity_ptr_array[G_entity_buffer->count] = G_entity_buffer->entity_chain_head;

    return (0);
}

int    ft_entityBufferUpdateArray()
{
    int         i;
    t_entity    *curr;

    free(G_entity_buffer->entity_ptr_array);
    G_entity_buffer->entity_ptr_array = malloc(sizeof(t_entity*) * (G_entity_buffer->count + 1));
    if (!G_entity_buffer->entity_ptr_array)
        return (ft_errorInt("failed to malloc ptr array", -1));

    curr = G_entity_buffer->entity_chain_head;
    i = 0;
    while (i <= G_entity_buffer->count)
    {
        G_entity_buffer->entity_ptr_array[i] = curr;
        curr = curr->next;
        i++;
    }
    return (0);
}

int ft_entityBufferPush(t_entity *entity)
{
    if (entity == NULL)
        return (ft_errorInt("entity pushed is NULL.", -1));

    entity->next = G_entity_buffer->entity_chain_head;
    G_entity_buffer->entity_chain_head->prev = entity;
    G_entity_buffer->entity_chain_head = entity;
    G_entity_buffer->count++;

    ft_entityBufferUpdateArray();

    return (0);
}

int ft_entityCreateGridMap(int size_x, int size_y, Texture2D *texture_ptr)
{
    t_entity    *grid_map_entity;

    grid_map_entity = ft_createEmptyEntityChain();
    if (grid_map_entity == NULL)
        return (-1);

    grid_map_entity->data_type = ENTITY_DATA_TYPE_GRID_MAP;
    grid_map_entity->data = (void*)ft_createGridMap(size_x, size_y, texture_ptr);
    if (grid_map_entity->data == NULL)
        return (ft_errorInt("failed to create gridMap entity", -1));
    grid_map_entity->ftptr_drawEntityMethod = ft_entityDrawGridMap;
    
    return (ft_entityBufferPush(grid_map_entity));
}

void    ft_entityDrawGridMap(int i)
{
    t_gridMap   *grid_map;

    if (G_entity_buffer->entity_ptr_array[i]->data_type != ENTITY_DATA_TYPE_GRID_MAP)
    {
        ft_error("index passed does not point to a gridMap entity.");
        return ;
    }
    grid_map = (t_gridMap*) G_entity_buffer->entity_ptr_array[i]->data;
    ft_drawGridMap(grid_map, 100, 100, 2.0f);
}

void    ft_drawEntityBuffer()
{
    int i;

    i = 0;
    while (i < G_entity_buffer->count)
    {
        if (G_entity_buffer->entity_ptr_array[i]->ftptr_drawEntityMethod != NULL)
            G_entity_buffer->entity_ptr_array[i]->ftptr_drawEntityMethod(i);
        i++;
    }
}

int main(void)
{
    InitWindow(1280, 720, "yeee");

    if (ft_initEntityBuffer() == -1)
    {
        CloseWindow();
        return (ft_errorInt("failed to create gridMap.", -1));
    }

    Texture2D   terrain_texture = LoadTexture("res/gridmap.png");

    ft_entityCreateGridMap(16, 16, &terrain_texture);

    //t_gridMap   *grid_map = ft_createGridMap(16, 16, &terrain_texture);
    /*
    if (!grid_map)
    {
        CloseWindow();
        return (ft_errorInt("failed to create gridMap.", -1));
    }
    for (int i = 0; i < grid_map->nb_tiles; i++)
        ft_gridMapSetTileTextureIndex(grid_map, i, GetRandomValue(0, 7));
    */


    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(GRAY);
            DrawText(TextFormat("CURRENT FPS: %i", GetFPS()), 0, 0, 20, GREEN);
            ft_drawEntityBuffer();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
