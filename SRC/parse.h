#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <draw.h>
#include <music.h>

int text_roll(FILE *file, int line_numbers[6], char (*array1)[64], char (*array2)[16], 
char (*image_filenames)[64], char (*music_filenames)[64], char (*sfx_filenames)[64], char (*ambiance_filenames)[64]);
void next_page(int *array, int size, int index);
int choice_picker();

//VN_Gamemodes

int parse_vnmode(int text_updated, int text_scroll, int size, FILE *file, int line_numbers[6], char (*textlines)[64], char (*choices)[16], char (*imagename)[64], char (*musicname)[64], char (*sfx_filenames)[64], char (*ambiance_filenames)[64]);

#endif
