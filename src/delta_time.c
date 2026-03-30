#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

static double freq = -1;
static Uint64 then = 0;
static Uint64 now = 1;

static double delta_current = 0.1f;
static const float delta_max = 75.0f;

static double delta_time = 0.1f;

void initDeltaFreq(void) {
	if (freq == -1) freq = SDL_GetPerformanceFrequency() / 1000.0f; //Seconds to Milliseconds
	return;
}

void setDeltaTime(void) {
	then = now;
	now = SDL_GetPerformanceCounter();

	delta_current = ((double)(now - then)) / freq;
	delta_time = delta_current < delta_max ? delta_current : delta_max;
}

double getDeltaTime(void) {
	return delta_time;
}

double getTotalTime(void) {
	return SDL_GetPerformanceCounter() / freq * 1000.0f;
}
