#include <SDL3/SDL_events.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

#include "app_metadata.h"
#include "delta_time.h"
#include "render.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

double delta = 1;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	for (int i = 1; i < argc; i++) SDL_LogInfo(0, "Passed arguement: %s", argv[i]);

	SDL_LogInfo(0, "Setting Metadata");
	if (!SET_APP_METADATA) SDL_LogWarn(0, "Couldn't set metadata: %s", SDL_GetError());

	SDL_LogInfo(0, "Initializing SDL3");
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogCritical(0, "%s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_LogInfo(0, "Creating Window And Renderer");
	if (!SDL_CreateWindowAndRenderer(APP_NAME, 800, 600, SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
		SDL_LogCritical(0, "%s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_LogInfo(0, "Initializing DeltaTime");
	initDeltaFreq();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	setDeltaTime();

	render(renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	SDL_LogInfo(0, "Closing SDL");
}
