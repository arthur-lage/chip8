#include <SDL3/SDL.h>

typedef struct Display {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Display;

int display_init(Display* display);
void display_quit(Display* display);
void display_clear(Display* display);