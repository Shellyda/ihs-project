#include "player.h"
#include "map.h"
#include "raylib.h"
#include "../include/ioctl_cmds.h"
#include <unistd.h>
#include <sys/ioctl.h>

static Vector2 pos = {100, 100};

static Texture2D texUp, texDown, texLeft, texRight, texUp2, texDown2, texLeft2, texRight2;
static Texture2D defaultUp, defaultDown, defaultLeft, defaultRight;

static char lastMove = 'd';
static bool isMoving = false;
static Sound stepSound;

void InitPlayer()
{
    defaultUp = LoadTexture("../../src/assets/sprites/player/defaultUp.png");
    defaultDown = LoadTexture("../../src/assets/sprites/player/defaultDown.png");
    defaultLeft = LoadTexture("../../src/assets/sprites/player/defaultLeft.png");
    defaultRight = LoadTexture("../../src/assets/sprites/player/defaultRight.png");

    texUp = LoadTexture("../../src/assets/sprites/player/movUp.png");
    texUp2 = LoadTexture("../../src/assets/sprites/player/movUp2.png");
    texDown = LoadTexture("../../src/assets/sprites/player/movDown.png");
    texDown2 = LoadTexture("../../src/assets/sprites/player/movDown2.png");
    texLeft = LoadTexture("../../src/assets/sprites/player/movLeft.png");
    texLeft2 = LoadTexture("../../src/assets/sprites/player/movLeft2.png");
    texRight = LoadTexture("../../src/assets/sprites/player/movRight.png");
    texRight2 = LoadTexture("../../src/assets/sprites/player/movRight2.png");

    stepSound = LoadSound("../../src/assets/sounds/step.wav");
}

static int currentFrame = 0;
static float frameTimer = 0.0f;
static const float frameSpeed = 0.2f;

void UpdatePlayer(int fd)
{
    Vector2 oldPos = pos;
    int key = 0;
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

    /*if (IsCollisionTile(pos))
    {
        pos = oldPos;
        isMoving = false;
    }*/
    else if (isMoving)
    {
        PlaySound(stepSound);

        frameTimer += GetFrameTime();

        if (frameTimer >= frameSpeed)
        {
            currentFrame = (currentFrame + 1) % 2;
            frameTimer = 0.0f;
        }
        else
        {
            currentFrame = 0;
            frameTimer = 0.0f;
        }
    }
}

void DrawPlayer()
{
    Vector2 position = {pos.x, pos.y};
    float scale = 0.25f;
    switch (lastMove)
    {
    case 'w':
        if (isMoving)
        {
            DrawTextureEx((currentFrame == 0) ? texUp : texUp2, position, 0.0f, scale, WHITE);
        }
        else
        {
            DrawTextureEx(defaultUp, position, 0.0f, scale, WHITE);
        }
        break;
    case 'a':
        if (isMoving)
        {
            DrawTextureEx((currentFrame == 0) ? texLeft : texLeft2, position, 0.0f, scale, WHITE);
        }
        else
        {
            DrawTextureEx(defaultLeft, position, 0.0f, scale, WHITE);
        }
        break;
    case 's':
        if (isMoving)
        {
            DrawTextureEx((currentFrame == 0) ? texDown : texDown2, position, 0.0f, scale, WHITE);
        }
        else
        {
            DrawTextureEx(defaultDown, position, 0.0f, scale, WHITE);
        }
        break;
    case 'd':
        if (isMoving)
        {
            DrawTextureEx((currentFrame == 0) ? texRight : texRight2, position, 0.0f, scale, WHITE);
        }
        else
        {
            DrawTextureEx(defaultRight, position, 0.0f, scale, WHITE);
        }
        break;
    }
}

void EndPlayer()
{
    UnloadTexture(texUp);
    UnloadTexture(texDown);
    UnloadTexture(texLeft);
    UnloadTexture(texRight);
    UnloadTexture(texUp2);
    UnloadTexture(texDown2);
    UnloadTexture(texLeft2);
    UnloadTexture(texRight2);
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
