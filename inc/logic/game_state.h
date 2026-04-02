#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

typedef struct player Player;
typedef struct pong Pong;
typedef struct gameState GameState;

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

extern void gameStateInit(GameState *gameState, int w, int h, const bool *kbState, double deltaTime);
extern void gameStateReset(GameState *gameState);

#endif
