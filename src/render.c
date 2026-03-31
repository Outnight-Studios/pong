#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "logic/game_state.h"

const int width = 800;
const int height = 600;

static const float scoreZoomMult = 4.2f;

void renderScore(GameState *gameState, SDL_Renderer *renderer) {
	SDL_SetRenderScale(renderer, scoreZoomMult, scoreZoomMult);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugTextFormat(
		renderer,
		(gameState->resolution.w / (2.0f * scoreZoomMult)) - gameState->playerBuffer,
		gameState->resolution.h / (32.0f * scoreZoomMult),
	 	"%d",
		gameState->player_left.points
	);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugTextFormat(
		renderer,
		(gameState->resolution.w / (2.0f * scoreZoomMult)) + gameState->playerBuffer,
		gameState->resolution.h / (32.0f * scoreZoomMult),
		"%d",
		gameState->player_right.points
	);

	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	return;
}

void renderBarrier(GameState *gameState, SDL_Renderer *renderer) {
	const SDL_FRect barrier = {
		0,
		gameState->resolution.w - 2,
		4,
		gameState->resolution.h
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderFillRect(renderer, &barrier);

	return;
}

void renderPlayers(GameState *gameState, SDL_Renderer *renderer) {
	const SDL_FRect left = {
		0 + gameState->playerBuffer,
		gameState->player_left.y - (gameState->playerHeight / 2.0f),
		gameState->playerWidth,
		gameState->playerHeight
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderFillRect(renderer, &left);

	const SDL_FRect right = {
		gameState->resolution.w - gameState->playerBuffer,
		gameState->player_right.y - (gameState->playerHeight / 2.0f),
		gameState->playerWidth,
		gameState->playerHeight,
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderFillRect(renderer, &right);

	return;
}

void renderPong(GameState *gameState, SDL_Renderer *renderer) {
	const SDL_FRect pong = {
			gameState->pong.x - (gameState->pongSides / 2.0f),
			gameState->pong.y - (gameState->pongSides / 2.0f),
			gameState->pongSides,
			gameState->pongSides,
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderFillRect(renderer, &pong);

	return;
}

int render(void *appstate, SDL_Renderer *renderer) {
	//Flushes and sets background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(renderer);
	GameState *gameState = (GameState *)appstate;

	renderScore(gameState, renderer);
	renderBarrier(gameState, renderer);
	renderPlayers(gameState, renderer);
	renderPong(gameState, renderer);

	SDL_RenderPresent(renderer);
	return 1;
}
