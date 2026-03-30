#ifndef APP_METADATA_H
#define APP_METADATA_H

#include <stdbool.h>
#include <SDL3/SDL_init.h>

#define APP_NAME "sdl_game"
#define APP_VERSION "0.0.0"
#define APP_IDENTIFIER "eu.outnight.sdl_game"
#define APP_CREATOR "Outnight Studios"
#define APP_COPYRIGHT "Copyright (c) Outnight Studios 2026"
#define APP_URL "https://outnight.eu"
#define APP_TYPE "game"

#define SET_APP_METADATA \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_NAME_STRING, APP_NAME) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_VERSION_STRING, APP_VERSION) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_IDENTIFIER_STRING, APP_IDENTIFIER) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, APP_CREATOR) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_COPYRIGHT_STRING, APP_COPYRIGHT) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_URL_STRING, APP_URL) && \
	SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, APP_TYPE)

#endif
