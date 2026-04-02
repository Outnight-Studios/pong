#include <stdbool.h>

#include <SDL3/SDL_stdinc.h>

static const float playerSpeed = 0.70f;
static const float pongSpeed = 0.25f;
static const float pongAcceleration = 0.067f;

static const unsigned int playerWidth = 8;
static const unsigned int playerHeight = 95;
//How far from the window's edges the player should be
static const unsigned int playerBuffer = 60;

//Center to edges
static const unsigned int pongSides = 24;


typedef struct resolution {
	unsigned int w;
	unsigned int h;
} Resolution;

typedef struct player {
	unsigned int points;
	float y;
	signed char y_direction;
} Player;

typedef struct pong {
	float x;
	float y;
	bool stuck;
	signed char x_direction;
	signed char y_direction;
} Pong;

typedef struct gameState {
	Resolution resolution;

	float playerSpeed;
	float pongSpeed;
	float pongAcceleration;

	unsigned int playerWidth;
	unsigned int playerHeight;
	unsigned int playerBuffer;

	unsigned int pongSides;

	const bool *keyboardState;

	Player player_left;
	Player player_right;

	Pong pong;

	double deltaTime;
} GameState;

void gameStateInit(GameState *gameState, int w, int h, const bool *kbState, double deltaTime) {
	gameState->resolution.w = w;
	gameState->resolution.h = h;

	gameState->playerSpeed = playerSpeed;
	gameState->pongSpeed = pongSpeed;
	gameState->pongAcceleration = pongAcceleration;

	gameState->playerWidth = playerWidth;
	gameState->playerHeight = playerHeight;
	gameState->playerBuffer = playerBuffer;

	gameState->pongSides = pongSides;

	gameState->keyboardState = kbState;

	gameState->player_left.points = 0;
	gameState->player_left.y = (int)(gameState->resolution.h/2);
	gameState->player_left.y_direction = 0;

	gameState->player_right.points = 0;
	gameState->player_right.y = (int)(gameState->resolution.h/2);
	gameState->player_right.y_direction = 0;

	gameState->pong.x = (int)(gameState->resolution.w/2);
	gameState->pong.y = SDL_rand(gameState->resolution.h) + 1;
	gameState->pong.stuck = false;
	gameState->pong.x_direction = SDL_rand(2) ? -1 : 1;
	gameState->pong.y_direction = SDL_rand(2) ? -1 : 1;

	gameState->deltaTime = deltaTime;

	return;
}

void gameStateReset(GameState *gameState) {
	gameState->player_left.y = (int)(gameState->resolution.h/2);
	gameState->player_left.y_direction = 0;


	gameState->playerSpeed = playerSpeed;
	gameState->pongSpeed = pongSpeed;


	gameState->player_right.y = (int)(gameState->resolution.h/2);
	gameState->player_right.y_direction = 0;

	gameState->pong.x = (int)(gameState->resolution.w/2);
	gameState->pong.y = SDL_rand(gameState->resolution.h) + 1;
	gameState->pong.stuck = false;
	gameState->pong.x_direction = SDL_rand(2) ? -1 : 1;
	gameState->pong.y_direction = SDL_rand(2) ? -1 : 1;

	return;
}
