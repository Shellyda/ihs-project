#include "game.h"
#include "player.h"
#include "map.h"
#include "raylib.h"

static Music music;
static int inBattle = 0;

static Camera2D camera;

void InitGame(int fd)
{
    InitAudioDevice();
    InitMap();
    InitPlayer();

    music = LoadMusicStream("../../src/assets/sounds/overworld.mp3");
    PlayMusicStream(music);

    camera.target = GetPlayerPosition(); 
    camera.offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 }; 
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void UpdateGame(int fd)
{
    UpdateMusicStream(music);
    UpdatePlayer(fd);

    camera.target = GetPlayerPosition();

    /*if (CheckGrassTrigger())
    {
        inBattle = 1;
        StopMusicStream(music);
        music = LoadMusicStream("../../src/assets/sounds/battle.mp3");
        PlayMusicStream(music);
    }*/
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera); 
    DrawMap();
    DrawPlayer();
    EndMode2D();

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
