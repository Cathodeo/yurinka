#include <music.h>

Mix_Chunk *current_sound = NULL;

int initialize_sdl_mixer() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        return -1;
    }
    Mix_AllocateChannels(8);
    return 0;
}

void play_ogg(const char *filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, 1);  // Play music indefinitely
    Mix_VolumeMusic(48);
}

void play_sfx(const char *filename) {
    // Free previous sound if exists
    if (current_sound != NULL) {
        Mix_FreeChunk(current_sound);
    }
    
    // Load the new sound effect
    current_sound = Mix_LoadWAV(filename);
    if (!current_sound) {
        printf("Failed to load sound effect: %s\n", Mix_GetError());
        return;
    }

    // Play the sound effect
    Mix_PlayChannel(1, current_sound, 0);  // Play once
}


void play_ambiance(const char *filename) {
    Mix_Chunk *ambiance_sound = Mix_LoadWAV(filename);
    if (!ambiance_sound) {
        printf("Failed to load ambiance sound: %s\n", Mix_GetError());
        return;
    }

    // Play the ambiance sound indefinitely
    if (Mix_PlayChannel(2, ambiance_sound, -1) == -1) {
        printf("Failed to play ambiance sound: %s\n", Mix_GetError());
    }
}


int stop_ambiance() {
    // Stop all currently playing sounds
    Mix_HaltChannel(-1);  // -1 halts all channels
    return 0;
}




void close_sdl_mixer() {
    Mix_CloseAudio();
    SDL_Quit();
}

