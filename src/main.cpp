#include "raylib.h"
#include "game/game.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "ioctl_cmds.h"

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
