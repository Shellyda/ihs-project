#include "player.h"
#include "map.h"
#include "raylib.h"
#include "./include/ioctl_cmds.h"
#include <unistd.h>

static Vector2 pos = {100, 100};

// Texturas de movimento
static Texture2D texUp, texDown, texLeft, texRight;
// Texturas default (parado)
static Texture2D defaultUp, defaultDown, defaultLeft, defaultRight;

static char lastMove = 'd';
static bool isMoving = false;
static Sound stepSound;

void InitPlayer()
{
    // Texturas default (parado)
    defaultUp = LoadTexture("assets/sprites/player/defaultUp.png");
    defaultDown = LoadTexture("assets/sprites/player/defaultDown.png");
    defaultLeft = LoadTexture("assets/sprites/player/defaultLeft.png");
    defaultRight = LoadTexture("assets/sprites/player/defaultRight.png");

    // Texturas de movimento
    texUp = LoadTexture("assets/sprites/player/movUp.png");
    texDown = LoadTexture("assets/sprites/player/movDown.png");
    texLeft = LoadTexture("assets/sprites/player/movLeft.png");
    texRight = LoadTexture("assets/sprites/player/movRight.png");

    stepSound = LoadSound("assets/audio/step.wav");
}

void UpdatePlayer(int fd)
{
    Vector2 oldPos = pos;
    int key = -1;
    ioctl(fd, RD_PBUTTONS);
    read(fd, &key, 1);

    isMoving = false;

    if (IsKeyDown(KEY_RIGHT) || key == 14)
    {
        pos.x += 2;
        lastMove = 'd';
        isMoving = true;
    }
    if (IsKeyDown(KEY_LEFT) || key == 7)
    {
        pos.x -= 2;
        lastMove = 'a';
        isMoving = true;
    }
    if (IsKeyDown(KEY_UP) || key == 13)
    {
        pos.y -= 2;
        lastMove = 'w';
        isMoving = true;
    }
    if (IsKeyDown(KEY_DOWN) || key == 11)
    {
        pos.y += 2;
        lastMove = 's';
        isMoving = true;
    }

    if (IsCollisionTile(pos))
    {
        pos = oldPos;
        isMoving = false; // colisão = não andou
    }
    else if (isMoving)
    {
        PlaySound(stepSound);
    }
}

void DrawPlayer()
{
    switch (lastMove)
    {
    case 'w':
        if (isMoving)
            DrawTexture(texUp, pos.x, pos.y, WHITE);
        else
            DrawTexture(defaultUp, pos.x, pos.y, WHITE);
        break;
    case 'a':
        if (isMoving)
            DrawTexture(texLeft, pos.x, pos.y, WHITE);
        else
            DrawTexture(defaultLeft, pos.x, pos.y, WHITE);
        break;
    case 's':
        if (isMoving)
            DrawTexture(texDown, pos.x, pos.y, WHITE);
        else
            DrawTexture(defaultDown, pos.x, pos.y, WHITE);
        break;
    case 'd':
        if (isMoving)
            DrawTexture(texRight, pos.x, pos.y, WHITE);
        else
            DrawTexture(defaultRight, pos.x, pos.y, WHITE);
        break;
    }
}

void EndPlayer()
{
    UnloadTexture(texUp);
    UnloadTexture(texDown);
    UnloadTexture(texLeft);
    UnloadTexture(texRight);
    UnloadTexture(defaultUp);
    UnloadTexture(defaultDown);
    UnloadTexture(defaultLeft);
    UnloadTexture(defaultRight);
    UnloadSound(stepSound);
}

Vector2 GetPlayerPosition()
{
    return pos;
}
