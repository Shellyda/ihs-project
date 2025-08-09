#include "map.h"
#include "player.h"
#include "raylib.h"

static Texture2D mapTex;
static Image collisionMask, grassMask;

void InitMap()
{
    mapTex = LoadTexture("assets/map.png");
    collisionMask = LoadImage("assets/tiles/collision_mask.png");
    grassMask = LoadImage("assets/tiles/grass.png");
}

void DrawMap()
{
    DrawTexture(mapTex, 0, 0, WHITE);
}

int IsCollisionTile(Vector2 pos)
{
    Color pixel = GetImageColor(collisionMask, pos.x, pos.y);
    return (pixel.r < 128);
}

int CheckGrassTrigger()
{
    Vector2 p = GetPlayerPosition();
    Color pixel = GetImageColor(grassMask, p.x, p.y);
    return (pixel.g > 128);
}

void EndMap()
{
    UnloadTexture(mapTex);
    UnloadImage(collisionMask);
    UnloadImage(grassMask);
}
