#include <stdio.h>
#include <string.h>
#include <parse.h>

BITMAP *buffer;

int text_roll(FILE *file, int line_numbers[6], char (*array1)[64], char (*array2)[16], 
char (*image_filenames)[64], char (*music_filenames)[64], char (*sfx_filenames)[64], char (*ambiance_filenames)[64]) {
    char parsebuff[256];  // Temporary buffer to read each line
    int current_line = 1;
    int line_index = 0;
    int array1_index = 0, array2_index = 0;
    int gamemode_id;

    // Keywords for special actions
    char next_background[] = "&background";
    char next_music[] = "&music";
    char next_sfx[] = "&sfx";
    char next_ambiance[] = "&ambiance";
    char halt_ambiance[] = "&stopambiance";
    char next_sprite[] = "&sprite";
    char next_gamemode[] = "&gamemode";

    // Reset file pointer to the beginning of the file
    rewind(file);

    // Read through the file line by line
    while (fgets(parsebuff, sizeof(parsebuff), file) != NULL) {
        // Check if the current line matches the specified line numbers
        if (current_line == line_numbers[line_index]) {
            // First 3 lines go into array1
            if (line_index < 3) {
                snprintf(array1[array1_index], 64, "%s", parsebuff);
                array1[array1_index][strcspn(array1[array1_index], "\n")] = '\0';  // Remove newline
                array1_index++;
            } else {
                // Check if the line starts with a special character "&"
                if (parsebuff[0] == '&') {
                    parsebuff[strcspn(parsebuff, "\n")] = '\0'; 
                    
                    // Extract the command and the filename/argument
                    char *command = strtok(parsebuff, " ");
                    if (command == NULL) continue; // Safety check for strtok

                    char *argument = strtok(NULL, " ");
                    if (argument == NULL) continue; // Ensure there's an argument

                    // Compare and trigger actions
                    if (strcmp(command, next_background) == 0 && argument) {
                        strcpy(image_filenames[0], argument); // Store the image filename
                        load_blit(image_filenames[0], buffer, 54, 18);  // Load the image
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        printf("DEBUG: Loaded Image: %s\n", argument);
                    } else if (strcmp(command, next_music) == 0 && argument) {
                        strcpy(music_filenames[0], argument); // Store the music filename
                        play_ogg(music_filenames[0]);
                        printf("DEBUG: Loaded OGG: %s\n", argument);  
                          
                    } 
						else if (strcmp(command, next_sfx) == 0 && argument) {
                        strcpy(sfx_filenames[0], argument); // Store the music filename
                        play_sfx(sfx_filenames[0]);
                        printf("DEBUG: Loaded SFX: %s\n", argument);  
                          
                    }
                    
                    else if (strcmp(command, next_ambiance) == 0 && argument) {
                        strcpy(ambiance_filenames[0], argument); // Store the music filename
                        play_ambiance(ambiance_filenames[0]);
                        printf("DEBUG: Loaded AMBIANCE: %s\n", argument);  
                          
                    }
                    
                    else if (strcmp(command, halt_ambiance) == 0) {
                        stop_ambiance();
                        printf("DEBUG: Stopped AMBIANCE");  
                          
                    }
						else if (strcmp(command, next_sprite) == 0 && argument) {
                        strcpy(image_filenames[1], argument); // Store the sprite filename
						 load_blit_transparent(image_filenames[1], buffer, 70, 18);  // Load the image
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        printf("DEBUG: Loaded Sprite: %s\n", argument);
                    } else if (strcmp(command, next_gamemode) == 0 && argument) {
						gamemode_id = atoi(argument);
						return gamemode_id;
						printf("DEBUG: Loaded mode number: %s\n", argument);
					}
                } else {
                    // Regular lines go into array2 (lines 4 to 6)
                    snprintf(array2[array2_index], 16, "%s", parsebuff);
                    array2[array2_index][strcspn(array2[array2_index], "\n")] = '\0';  // Remove newline
                    array2_index++;
                }
            }
            line_index++;
            // Stop if all 6 lines are processed
            if (line_index >= 6) {
                break;
            }
        }  
        current_line++;
    }

    // Safely terminate any remaining elements in array1 or array2
    while (array1_index < 3) {
        array1[array1_index][0] = '\0';  // Empty string
        array1_index++;
    }
    while (array2_index < 3) {
        array2[array2_index][0] = '\0';  // Empty string
        array2_index++;
    }
    return 1;
}

void next_page(int *array, int size, int index) {
	play_sfx("SFX/NEXT.WAV");
    // Base case: stop when the index reaches the size of the array
    if (index == size) {
        return;
    }

    // Add 6 to the current element
    array[index] += 6;

    // Recursive case: process the next element
    next_page(array, size, index + 1);
}

int choice_picker() {
    if ( (mouse_y > 415 && mouse_y < 439) && (mouse_x > 58 && mouse_x < 227) && (mouse_b & 1))
        return 1;
    if ( (mouse_y > 415 && mouse_y < 439) && (mouse_x > 237 && mouse_x < 406) && (mouse_b & 1))
        return 2;
    if ( (mouse_y > 415 && mouse_y < 439) && (mouse_x > 416 && mouse_x < 585) && (mouse_b & 1))
        return 3;

    return 0;  // Return 0 if no choice is picked
}

// Gamemode VN:
int parse_vnmode(int text_updated, int text_scroll, int size, FILE *file, int line_numbers[6], char (*textlines)[64], char (*choices)[16], char (*imagename)[64], char (*musicname)[64], char (*sfx_filenames)[64], char (*ambiance_filenames)[64]) {
    int nextmode = 1;
	
    if (key[KEY_ENTER] && text_updated == 0 && text_scroll == 1) {
        next_page(line_numbers, size, 0);
        nextmode = text_roll(file, line_numbers, textlines, choices, imagename, musicname, sfx_filenames, ambiance_filenames); // Parse the new text
        text_updated = 1;                                  // Mark the text as updated
        rest(100);                                         // Delay to debounce the keypress
    }

    // Draw the text and choices                
    triple_dialog(textlines[0], textlines[1], textlines[2]);
    choice_picker_base(buffer, 3);
    choice_picker_text(choices[0], choices[1], choices[2], 3);

    // Blit the buffer to the screen
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    rest(30);

    // Reset text_updated when the key is released
    if (!key[KEY_ENTER]) {
        text_updated = 0;  // Allow text update on next key press
    }

    return nextmode;
}

