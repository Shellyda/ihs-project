#include "raylib.h"
#include "game/game.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "ioctl_cmds.h"
#include <stdio.h>

bool waitUser(int fd)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("PokeCIn", 300, 200, 40, WHITE);
        DrawText("Press ENTER to start", 200, 300, 20, WHITE);
        EndDrawing();

        int key = 0;
        ioctl(fd, RD_SWITCHES);
        read(fd, &key, 1); // 1 byte -> 8 bits -> 8 switches

        // SWITCH - INPUT
        if (IsKeyPressed(KEY_ENTER) || key > 0)
            return true;

        // SHOW DISPLAY AND LEDS

        unsigned int data = 0x0;
        ioctl(fd, WR_GREEN_LEDS);
        write(fd, &data, sizeof(data));

        sleep(1);

        data = 0xFFFFFFFF;
        ioctl(fd, WR_GREEN_LEDS);
        write(fd, &data, sizeof(data));
        sleep(1);

        data = 0x0;
        ioctl(fd, WR_GREEN_LEDS);
        write(fd, &data, sizeof(data));

        data = 0xFFFFFFFF;
        ioctl(fd, WR_RED_LEDS);
        write(fd, &data, sizeof(data));

        sleep(1);

        data = 0x0;
        ioctl(fd, WR_RED_LEDS);
        write(fd, &data, sizeof(data));

        data = 0x0;
        ioctl(fd, WR_L_DISPLAY);
        write(fd, &data, sizeof(data));

        sleep(1);

        data = 0xFFFFFFFF;
        ioctl(fd, WR_L_DISPLAY);
        write(fd, &data, sizeof(data));

        data = 0x0;
        ioctl(fd, WR_R_DISPLAY);
        write(fd, &data, sizeof(data));

        sleep(1);

        data = 0xFFFFFFFF;
        ioctl(fd, WR_R_DISPLAY);
        write(fd, &data, sizeof(data));
    }
    return false;
}

int main(int argc, char **argv)
{
    int fd;

    if (argc < 2)
    {
        printf("Syntax: %s <device file path>\n", argv[0]);
        return -EINVAL;
    }

    if ((fd = open(argv[1], O_RDWR)) < 0)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return -EBUSY;
    }

    InitWindow(800, 600, "PokeCIn");
    SetTargetFPS(60);

    if (!waitUser(fd))
    {
        CloseWindow();
        if (fd >= 0)
            close(fd);
        return 0;
    }

    InitGame(fd);

    while (!WindowShouldClose())
    {
        UpdateGame(fd);
        DrawGame();
    }

    EndGame();

    if (fd >= 0)
        close(fd);

    CloseWindow();
    return 0;
}
