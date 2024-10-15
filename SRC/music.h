#ifndef MUSIC_H
#define MUSIC_H

#include <allegro.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int initialize_sdl_mixer();
void play_ogg(const char *filename);
void play_sfx(const char *filename);
void play_ambiance(const char *filename);
int stop_ambiance();
void close_sdl_mixer();


#endif
