#include <stdio.h>
#include "map.h"
#include "player.h"
#include "raylib.h"

static Texture2D mapTex;
static Image collisionMask, grassMask;

void InitMap()
{
    const char *mapPath = "../../src/assets/map.png";
    const char *collisionPath = "../../src/assets/tiles/collision_mask.png";
    const char *grassPath = "../../src/assets/tiles/grass.png";

    if (FileExists(mapPath))
    {
        mapTex = LoadTexture(mapPath);
    }
    else
    {
        printf("ERRO: Map file not found into: %s\n", mapPath);
        mapTex.id = 0;
    }

    if (FileExists(collisionPath))
    {
        collisionMask = LoadImage(collisionPath);
    }
    else
    {
        printf("ERRO: collision file not found into: %s\n", collisionPath);
        collisionMask.data = NULL;
    }

    if (FileExists(grassPath))
    {
        grassMask = LoadImage(grassPath);
    }
    else
    {
        printf("ERRO: Grass file not found into: %s\n", grassPath);
        grassMask.data = NULL;
    }
}

void DrawMap()
{
    if (mapTex.id != 0)
        DrawTexture(mapTex, 0, 0, WHITE);
}

int IsCollisionTile(Vector2 pos)
{
    if (collisionMask.data == NULL)
        return 0;
    Color pixel = GetImageColor(collisionMask, pos.x, pos.y);
    return (pixel.r < 128);
}

int CheckGrassTrigger()
{
    if (grassMask.data == NULL)
        return 0;
    Vector2 p = GetPlayerPosition();
    Color pixel = GetImageColor(grassMask, p.x, p.y);
    return (pixel.g > 128);
}

void EndMap()
{
    if (mapTex.id != 0)
        UnloadTexture(mapTex);
    if (collisionMask.data != NULL)
        UnloadImage(collisionMask);
    if (grassMask.data != NULL)
        UnloadImage(grassMask);
}
