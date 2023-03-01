/**
 * A simple GUI example. You can move the employee using
 * the keyboard arrows. Press `q` or close the window to quit.
 *
 */

#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "gui.h"

void print_level(int width, int height, char level[height][width]) {
    printf("print level\n");
    for (int line = 0; line < height; line++)
        for (int col = 0; col < width; col++)
            GUI_show(col, line, level);
}

void go_dir(int width, int height, char level[height][width],
            int delta_x, int delta_y, int *p_x, int *p_y) {
    int new_x = *p_x + delta_x;
    int new_y = *p_y + delta_y;

    if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
        return;
    }

    level[new_y][new_x] = '@';
    level[*p_y][*p_x]   = ' ';

    *p_x = new_x;
    *p_y = new_y;
}

int main(int argc, char *argv[]) {
    // define a simple level
    char level[10][10] = { [0 ... 9][0 ... 9] = ' ' };
    int  x             = 4;
    int  y             = 4;
    bool stop          = false;

    // put player on cell (4, 4)
    level[x][y] = '@';

    // put a wall on cell (0, 0)
    level[0][0] = '#';

    // initialize GUI window
    GUI_init("Sokoban", 10, 10);

    // display level
    GUI_show(10, 10, level);

    // main loop
    while(true) {

        switch (GUI_get_key()) {
        case SDLK_UP:
            go_dir(10, 10, level, 0, -1, &x, &y);
            GUI_show(10, 10, level);
            break;
        case SDLK_DOWN:
            go_dir(10, 10, level, 0, 1, &x, &y);
            GUI_show(10, 10, level);
            break;
        case SDLK_LEFT:
            go_dir(10, 10, level, -1, 0, &x, &y);
            GUI_show(10, 10, level);
            break;
        case SDLK_RIGHT:
            go_dir(10, 10, level, 1, 0, &x, &y);
            GUI_show(10, 10, level);
            break;
        case 'q':
            stop = true;
            break;
        case -1:
            stop = true;
            break;
        }

        if (stop) {
            break;
        }
    }

    GUI_close();

    return EXIT_SUCCESS;
}
