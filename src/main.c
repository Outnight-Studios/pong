#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_stdinc.h>

#include "app_metadata.h"
#include "render.h"

#include "logic/delta_time.h"
#include "logic/game_state.h"
#include "logic/loop.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	//Parsing Arguements
	for (int i = 1; i < argc; i++) SDL_LogInfo(0, "Passed arguement: %s", argv[i]);

	//SDL Specific Stuff
	SDL_LogInfo(0, "Setting Metadata");
	if (!SET_APP_METADATA) SDL_LogWarn(0, "Couldn't set metadata: %s", SDL_GetError());

	SDL_LogInfo(0, "Initializing SDL3");
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogCritical(0, "%s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_LogInfo(0, "Creating Window And Renderer");
	if (!SDL_CreateWindowAndRenderer(APP_NAME, width, height, SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
		SDL_LogCritical(0, "%s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	//DeltaTime
	SDL_LogInfo(0, "Initializing DeltaTime");
	initDeltaFreq();

	//Game State Stuff
	SDL_LogInfo(0, "Setting Game State");
	GameState *gameState = SDL_calloc(1, sizeof(GameState));
	if (!gameState) {
		SDL_LogCritical(0, "Out of Memory: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	gameStateInit(
		gameState,
		width,
		height,
		SDL_GetKeyboardState(NULL),
		deltaTime()
	);
	*appstate = gameState;

	SDL_LogInfo(0, "Initialization Completed");
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	GameState *gameState = (GameState *)appstate;
	gameState->deltaTime = deltaTime();
	SDL_PumpEvents();

	update(appstate);
	render(appstate, renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	SDL_LogInfo(0, "Closing SDL");
	SDL_free(appstate);
}
