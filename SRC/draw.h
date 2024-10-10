// draw.h
#ifndef DRAW_H
#define DRAW_H

#include <allegro.h>
#include <stdio.h>

extern BITMAP *buffer;
// Declare the function that will be defined in draw.c
void draw_dialog_base(BITMAP* buffer);
void choice_picker_base(BITMAP* buffer, int n_choices);
void choice_picker_text(const char *choice1, const char *choice2, const char *choice3, int n_choices);
void triple_dialog(const char *text1, const char *text2, const char *text3);
void load_blit(const char *image_path, BITMAP *buffer, int dst_x, int dst_y);
void load_blit_transparent(const char *image_path, BITMAP *buffer, int dst_x, int dst_y);

#endif  // End of include guard
