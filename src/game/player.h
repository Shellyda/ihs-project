#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

void InitPlayer();
void UpdatePlayer(int fd);
void DrawPlayer();
void EndPlayer();

Vector2 GetPlayerPosition();

#endif
