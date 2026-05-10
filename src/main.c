#include "game.h"
#include "raylib.h"

t_entityBuffer   *G_entity_buffer = NULL;

int main(void)
{
    InitWindow(1280, 720, "yeee");

    if (ft_initEntityBuffer() == -1)
    {
        CloseWindow();
        return (ft_errorInt("failed to create gridMap.", -1));
    }

    Texture2D   terrain_texture = LoadTexture("res/gridmap.png");

    t_entity    *grid_map_entity = ft_entityCreateGridMap(16, 16, &terrain_texture);
    t_gridMap   *grid_map = (t_gridMap*)grid_map_entity->data;

    for (int i = 0; i < grid_map->nb_tiles; i++)
        ft_gridMapSetTileTextureIndex(grid_map, i, GetRandomValue(0, 7));

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(GRAY);
            DrawText(TextFormat("CURRENT FPS: %i", GetFPS()), 0, 0, 20, GREEN);
            ft_drawEntityBuffer();
        EndDrawing();
    }

    ft_freeEntityBuffer();

    CloseWindow();

    return 0;
}
