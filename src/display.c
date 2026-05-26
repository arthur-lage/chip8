#include <SDL3/SDL.h>
#include "display.h"

int display_init(Display* display) {
    SDL_SetAppMetadata("Chip8", "v1.0.0", "com.arthurlage.chip8");

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    if(props == 0) {
        SDL_Log("Unable to create properties: %s", SDL_GetError());
        return 0;
    }

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Chip 8");
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, false);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 640);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 480);

    SDL_Window *window = SDL_CreateWindowWithProperties(props);
    if(window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 0;
    }
    SDL_ShowWindow(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    display->window = window;
    display->renderer = renderer;

    return 0;
}

void display_quit(Display* display) {
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}

void display_clear(Display* display) {
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
    SDL_RenderPresent(display->renderer);
}