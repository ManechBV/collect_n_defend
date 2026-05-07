#include "game.h"
#include "raylib.h"

int main(void)
{
    InitWindow(1280, 720, "yeee");

    Texture2D   terrain_texture = LoadTexture("res/gridmap.png");
    t_gridMap   *grid_map = ft_createGridMap(16, 16, &terrain_texture);
    if (!grid_map)
    {
        CloseWindow();
        return (ft_errorInt("failed to create gridMap.", -1));
    }

    for (int i = 0; i < grid_map->nb_tiles; i++)
        ft_gridMapSetTileTextureIndex(grid_map, i, GetRandomValue(0, 7));

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(GRAY);
            DrawText(TextFormat("CURRENT FPS: %i", GetFPS()), 0, 0, 20, GREEN);
            ft_drawGridMap(grid_map, 100, 100, 2.0);
        EndDrawing();
    }

    ft_freeGridMap(grid_map);

    CloseWindow();

    return 0;
}
