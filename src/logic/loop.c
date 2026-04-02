#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_scancode.h>

#include "logic/game_state.h"

void movePlayers(GameState *gameState) {
	if (!(gameState->keyboardState[SDL_SCANCODE_W] && gameState->keyboardState[SDL_SCANCODE_S])) {
		//Change if inverted
		if (gameState->keyboardState[SDL_SCANCODE_W] && ((0 + gameState->playerHeight / 2.0) < gameState->player_left.y)) {
			gameState->player_left.y_direction = -1;
		}
		else if (gameState->keyboardState[SDL_SCANCODE_S] && (gameState->player_left.y < (gameState->resolution.h - gameState->playerHeight / 2.0))) {
			gameState->player_left.y_direction = 1;
		}
		else gameState->player_left.y_direction = 0;
	}
	gameState->player_left.y += gameState->playerSpeed * gameState->player_left.y_direction * gameState->deltaTime;

	if (!(gameState->keyboardState[SDL_SCANCODE_UP] && gameState->keyboardState[SDL_SCANCODE_DOWN])) {
		//Change if inverted
		if (gameState->keyboardState[SDL_SCANCODE_UP] && ((0 + gameState->playerHeight / 2.0) < gameState->player_right.y)) {
			gameState->player_right.y_direction = -1;
		}
		else if (gameState->keyboardState[SDL_SCANCODE_DOWN] && (gameState->player_right.y < (gameState->resolution.h - gameState->playerHeight / 2.0))) {
			gameState->player_right.y_direction = 1;
		}
		else gameState->player_right.y_direction = 0;
	}

	gameState->player_right.y += gameState->playerSpeed * gameState->player_right.y_direction * gameState->deltaTime;

	return;
}

void movePong(GameState *gameState) {
	gameState->pong.x += gameState->pongSpeed * gameState->pong.x_direction * gameState->deltaTime;
	gameState->pong.y += gameState->pongSpeed * gameState->pong.y_direction * gameState->deltaTime;

	//Hit pong back
	//If within the bounds of the paddle, change direction
	const SDL_FRect left = {
		0 + gameState->playerBuffer,
		gameState->player_left.y - (gameState->playerHeight / 2.0f),
		gameState->playerWidth,
		gameState->playerHeight,
	};

	const SDL_FRect right = {
		gameState->resolution.w - gameState->playerBuffer,
		gameState->player_right.y - (gameState->playerHeight / 2.0f),
		gameState->playerWidth,
		gameState->playerHeight,
	};

	const SDL_FRect pong = {
		gameState->pong.x - (gameState->pongSides / 2.0f),
		gameState->pong.y - (gameState->pongSides / 2.0f),
		gameState->pongSides,
		gameState->pongSides,
	};

	//If not stuck (i.e., already bouncing while satisfying the conditions to bounce), then bounce and increase speed
	if (!gameState->pong.stuck) {
		if (SDL_HasRectIntersectionFloat(&left, &pong) || SDL_HasRectIntersectionFloat(&right, &pong)) {
			gameState->pong.x_direction = -gameState->pong.x_direction;
			gameState->pongSpeed *= (1.0f + gameState->pongAcceleration);
			gameState->playerSpeed *= (1.0f + gameState->pongAcceleration);
		}

		//Bounce on top and bottom of screen
		if (gameState->pong.y < (0 + gameState->pongSides / 2.0) || gameState->pong.y > (gameState->resolution.h - gameState->pongSides / 2.0)) {
			gameState->pong.y_direction = -gameState->pong.y_direction;
		}

	}

	//If neither of this are true, pong is not stuck
	gameState->pong.stuck = (
		SDL_HasRectIntersectionFloat(&left, &pong) ||
		SDL_HasRectIntersectionFloat(&right, &pong)
	) ||
	(
		gameState->pong.y < (0 + gameState->pongSides / 2.0) ||
		gameState->pong.y > (gameState->resolution.h - gameState->pongSides / 2.0)
	);

	return;
}

void checkWinning(GameState *gameState) {
	//Score goal if over the screen sides
	if (gameState->pong.x < 0) {
		gameState->player_right.points++;
		gameStateReset(gameState);
	}
	else if (gameState->pong.x > gameState->resolution.w) {
		gameState->player_left.points++;
		gameStateReset(gameState);
	}

	return;
}

void update(void *appstate) {
	GameState *gameState = appstate;

	movePlayers(gameState);
	movePong(gameState);
	checkWinning(gameState);

	return;
}
