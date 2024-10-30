// draw.h
#ifndef DRAW_H
#define DRAW_H

#include <allegro.h>
#include <stdio.h>
#include <music.h>
#include <battle.h>
#include <battle_data.h>

extern BITMAP *buffer;
// Declare the function that will be defined in draw.c
void typewriter_text(BITMAP *buffer, const char *text, int x, int y, int color);
void draw_gradient_background(BITMAP* buffer, int x1, int y1, int x2, int y2);
void draw_dialog_base(BITMAP* buffer);
void draw_battleui_base(BITMAP* buffer);
void display_enemy_choices(int enemy1, int enemy2, int enemy3);
void draw_portrait(BITMAP* buffer, const char *image_path);
const char* get_hp_status(int current_hp, int max_hp);
void draw_hp_bar(BITMAP* buffer, int current_hp, int max_hp, int x, int y, int width, int height);
void draw_hp_status(BITMAP* buffer, int current_hp, int max_hp, int x, int y);
void draw_move_card(BITMAP *buffer, int move_id, int w);
void chara_info(BITMAP* buffer, int char_id, int current_hp, int status_id);
void draw_battle_ui(BITMAP* buffer, int current_hp, int max_hp, int char_id, int status_id);
void choice_picker_base(BITMAP* buffer, int n_choices);
void choice_picker_text(const char *choice1, const char *choice2, const char *choice3, int n_choices);
void triple_dialog(const char *text1, const char *text2, const char *text3);
void triple_dialog_typewriter(const char *text1, const char *text2, const char *text3);
void load_blit(const char *image_path, BITMAP *buffer, int dst_x, int dst_y);
void load_blit_transparent(const char *image_path, BITMAP *buffer, int dst_x, int dst_y);
void load_battle_background(BITMAP *buffer, int battle_id);
void load_battle_foe(BITMAP *buffer, int battle_id, int foe_index, int w);
void display_attack_info(int selection, int character);
void draw_superui();
void display_ally_choices(int ally1, int ally2, int ally3);
void battle_message(const char *message);
void battle_message_row2(const char *message);

#endif  // End of include guard
