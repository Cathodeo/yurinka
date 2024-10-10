#include <music.h>

void play_background_music(const char* filename) {
    MIDI* midi = load_midi(filename);
    if (midi) {
        play_midi(midi, 1); // Play music
    } else {
        allegro_message("Error loading music file!");
    }
}