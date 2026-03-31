#ifndef RENDER
#define RENDER

#include <SDL3/SDL_render.h>

extern const int width;
extern const int height;

extern void render(void *appstate, SDL_Renderer *renderer);

#endif
