#include <SDL3/SDL_render.h>

#include "delta_time.h"

int render(SDL_Renderer *renderer) {
	double now = getTotalTime() * 0.000005f;

	SDL_RenderClear(renderer);
	const float red = 0.5 + 0.5 * SDL_sin(now);
	const float green = 0.5 + 0.5 * SDL_sin(now + SDL_PI_F * 2/3);
	const float blue = 0.5 + 0.5 * SDL_sin(now + SDL_PI_F * 4/3);
	SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

	SDL_RenderPresent(renderer);
	return 1;
}
