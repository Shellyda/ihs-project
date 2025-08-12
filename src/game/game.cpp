#include "game.h"
#include "player.h"
#include "map.h"
#include "raylib.h"

static Music music;
static int inBattle = 0;

void InitGame(int fd)
{
    InitAudioDevice();
    InitMap();
    InitPlayer();

    music = LoadMusicStream("../../src/assets/sounds/overworld.mp3");
    PlayMusicStream(music);
}

void UpdateGame(int fd)
{
    UpdateMusicStream(music);
    UpdatePlayer(fd);

    if (CheckGrassTrigger())
    {
        inBattle = 1;
        StopMusicStream(music);
        music = LoadMusicStream("../../src/assets/sounds/battle.mp3");
        PlayMusicStream(music);
    }
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawMap();
    DrawPlayer();

    if (inBattle)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
        DrawText("BATTLE!", 300, 250, 40, WHITE);
    }

    EndDrawing();
}

void EndGame()
{
    EndPlayer();
    EndMap();
    UnloadMusicStream(music);
    CloseAudioDevice();
}
