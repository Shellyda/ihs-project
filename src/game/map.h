#ifndef MAP_H
#define MAP_H

#include "raylib.h"

void InitMap();
void DrawMap();
void EndMap();
int IsCollisionTile(Vector2 pos);
int CheckGrassTrigger();

#endif
