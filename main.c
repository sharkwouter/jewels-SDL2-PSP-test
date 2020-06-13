#include <SDL2/SDL.h>
#include <stdio.h>

#define NAME "Jewels"
#define WIDTH 480
#define HEIGHT 272

int closed = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int setupSdl() {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);

    window = SDL_CreateWindow(
        NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        SDL_Log("Failed to initiation window. Error %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Failed to initialize renderer. Error: %s", SDL_GetError());
        return 1;
    }

    return 0;
}

void handleEvents(){
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = 1;
                break;
        }
    }
}

int game(int argc, char *argv[]){
    printf("Starting game\n");
    if (setupSdl() != 0) {
        return 1;
    }

    // load image
    SDL_Surface* surface = NULL;
    surface = SDL_LoadBMP("block.bmp");
    if (surface == NULL) {
        SDL_Log("Unable to load image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* block = NULL;
    block = SDL_CreateTextureFromSurface(renderer, surface);
    if (block == NULL) {
        SDL_Log("Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* block2 = NULL;
    block2 = SDL_CreateTextureFromSurface(renderer, surface);
    if (block2 == NULL) {
        SDL_Log("Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* block3 = NULL;
    block3 = SDL_CreateTextureFromSurface(renderer, surface);
    if (block3 == NULL) {
        SDL_Log("Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* block4 = NULL;
    block4 = SDL_CreateTextureFromSurface(renderer, surface);
    if (block4 == NULL) {
        SDL_Log("Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_FreeSurface(surface);

    // Create SDL rect
    SDL_Rect sourceRect = {0, 0, 32, 32};
    SDL_Rect blockRect = {WIDTH/2, HEIGHT/2, 32, 32};

    //Create some additional rects for other tests
    SDL_Rect smallRect = {50, HEIGHT/2, 16, 16};
    SDL_Rect bigRect = {400, HEIGHT/2, 64, 64};

    SDL_Rect partialRect = {150, HEIGHT/2, 32, 32};
    SDL_Rect partialSourceRect = {0, 0, 16, 16};
    SDL_Rect partialSourceCorrectRect = {300, HEIGHT/2, 16, 16};

    while (!closed) {
        handleEvents();
        SDL_RenderCopy(renderer, block, &sourceRect, &blockRect);
        SDL_RenderCopy(renderer, block, &sourceRect, &smallRect);
        SDL_RenderCopy(renderer, block, &sourceRect, &bigRect);
        SDL_RenderCopy(renderer, block, &partialSourceRect, &partialRect);
        SDL_RenderCopy(renderer, block, &partialSourceRect, &partialSourceCorrectRect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }
    return 0;
}

#ifdef __PSP__
int SDL_main(int argc, char *argv[]) {
    return game(argc, argv);
}
#else
int main(int argc, char *argv[]) {
    return game(argc, argv);
}
#endif
