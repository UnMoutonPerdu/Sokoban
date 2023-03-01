#include <SDL2/SDL.h>
#include <signal.h>
#include "gui.h"

/** Sokoban icon size. */
#define ICON_SIZE 32

/** @brief The SDL renderer. */
static SDL_Renderer *renderer;

/** @brief The SDL window. */
static SDL_Window *window;

/** @brief An array containing all images */
static SDL_Surface *images[7];

/** @brief An array containing all textures */
static SDL_Texture *textures[7];

/**
 * @brief An enumeration to represent all symbols.
 *
 * It can be used to ease the readibility of your code.
 *
 */
enum object { BOY, BOY_ON, BOX, BOX_ON, PARK, WALL, EMPTY };

/**
 * @brief The set of `char` values used to represent maps.
 *
 */
static char symbols[] = { '@', '+', '$', '*', '.', '#', ' ' };

/**
 * @brief The locations of the bitmap images to use.
 *
 * The files must be given in the same order as the symbols.
 */
static char* image_filename[] = {
    "images/yoshi-32-worker.bmp",
    "images/yoshi-32-worker-docked.bmp",
    "images/yoshi-32-box.bmp",
    "images/yoshi-32-box-docked.bmp",
    "images/yoshi-32-dock.bmp",
    "images/yoshi-32-wall.bmp",
    "images/yoshi-32-floor.bmp"
};

void GUI_close() {
#ifdef GUI
    for (int obj = BOY; obj <= EMPTY; obj++) {
        SDL_DestroyTexture(textures[obj]);
        textures[obj] = NULL;
    }

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    //exit(EXIT_SUCCESS);
#endif
}

void GUI_init(char *title, int width, int height) {
#ifdef GUI
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error in SDL_Init: %s\n", SDL_GetError());
        exit(-1);
    }

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width * ICON_SIZE,
                              height * ICON_SIZE,
                              0);

    if (window == NULL) {
        fprintf(stderr, "Error in SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL) {
        fprintf(stderr, "Error in SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
    SDL_EventState(SDL_QUIT,    SDL_ENABLE);

    for (int obj = BOY; obj <= EMPTY; obj++) {
        images[obj] = SDL_LoadBMP(image_filename[obj]);

        if (!images[obj]) {
            fprintf(stderr, "Missing image %s\n", image_filename[obj]);
            exit(1);
        }

        textures[obj] = SDL_CreateTextureFromSurface(renderer, images[obj]);
        SDL_FreeSurface(images[obj]);
    }
#endif
}

void GUI_show(int width, int height, char level[height][width]) {
#ifdef GUI
    SDL_RenderClear(renderer);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            SDL_Rect area = {
                col * ICON_SIZE,
                row * ICON_SIZE,
                ICON_SIZE,
                ICON_SIZE };

            for (int obj = BOY; obj <= EMPTY; obj++) {
                if (level[row][col] == symbols[obj]) {
                    SDL_RenderCopy(renderer, textures[obj], NULL, &area);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
#endif
}

int GUI_get_key() {
    SDL_Event event;

    do {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            GUI_close();
            return -1;
        }

    } while (event.type != SDL_KEYDOWN);

    return event.key.keysym.sym;
}

void GUI_wait_click()
{
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
    SDL_Event event;

    do {
        SDL_WaitEvent(&event);
    } while (event.type!=SDL_MOUSEBUTTONDOWN);

    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
}

void GUI_pause(int time) {
    SDL_Delay(time);
}
