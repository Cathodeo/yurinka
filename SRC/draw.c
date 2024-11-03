#include <draw.h> 
#include <math.h>

#define LINE_SPACING 20     
#define TEXTBOX_WPOS 58
#define TEXTBOX_HPOS 354 
#define TEXTBOX_WIDTH 524
#define CHOICE_HEIGHT 20
#define CHOICE_Y_OFFSET 420
#define CHOICE_COLOR makecol(173, 216, 230) // Light blue for choice boxes
#define CHOICE_SPACING 10
#define MAX_LINE_LENGTH 64     // Maximum number of characters per line
#define CHAR_DELAY 5   
#define DARK_RED makecol(139, 0, 0)
#define RED makecol(255, 0, 0)
#define ORANGE makecol(255, 165, 0)
#define YELLOW makecol(255, 255, 0)
#define GREEN makecol(0, 255, 0)
#define TEAL makecol(0, 128, 128)
#define BLUE makecol(0, 0, 255)  
#define PURPLE makecol(0, 125, 255)    

// Function to render a single line of text with typewriter effect
void typewriter_text(BITMAP *buffer, const char *text, int x, int y, int color) {
    char line[MAX_LINE_LENGTH + 1];  // Buffer to hold the line of text (including null terminator)
    int line_pos = 0;                // Current position in the line
    int len = strlen(text);          // Length of the text
    int char_limit = (len < MAX_LINE_LENGTH) ? len : MAX_LINE_LENGTH; // Limit to 64 characters

    // Iterate over the characters of the string (up to 64 characters max)
    for (int i = 0; i < char_limit; i++) {
        line[line_pos++] = text[i];         // Add the current character to the line buffer
        line[line_pos] = '\0';              // Null-terminate the string
        textout_ex(buffer, font, line, x, y, color, -1);  // Draw the line up to the current character
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);  // Update the screen
        rest(CHAR_DELAY);                   // Delay between character rendering
    }
}

void draw_gradient_background(BITMAP* buffer, int x1, int y1, int x2, int y2) {
    // Draw a vertical gradient with various tones of blue
    for (int i = y1; i <= y2; i++) {
        int color = makecol(0, 0 + (i - y1) * (250 / (y2 - y1)), (250 - (i / 2))); // Gradient from light to darker blue
        hline(buffer, x1, i, x2, color);
    }
}

void draw_dialog_base(BITMAP* buffer) {
    // Clear screen and fill background with gradient
    draw_gradient_background(buffer, 0, 0, SCREEN_W, SCREEN_H);
    // Draw a smaller rectangle inside the screen bounds
    rectfill(buffer, 54, 18, 578, 320, makecol(55, 55, 55));  // Medium blue rectangle for dialog
    rect(buffer, 52, 338, 582, 412, makecol(0, 0, 120));
}


void draw_battleui_base(BITMAP* buffer) {
	draw_gradient_background(buffer, 0, 0, SCREEN_W, SCREEN_H);
	rectfill(buffer, 166, 325, 578, 345, makecol(0, 0, 120));
	rectfill(buffer, 166, 328, 324, 343, makecol(0, 0, 200));
	rectfill(buffer, 344, 328, 558, 343, makecol(0, 0, 200));
	rectfill(buffer, 54, 336, 156, 440, makecol(0, 0, 120));
	rectfill(buffer, 166, 365, 578, 440, makecol(0, 0, 120));
	rectfill(buffer, 169, 368, 575, 438, makecol(0, 0, 200));
	rectfill(buffer, 54, 375, 578, 440, makecol(0, 0, 120));
	rectfill(buffer, 57, 378, 575, 438, makecol(0, 0, 200));
	
}

void draw_portrait(BITMAP* buffer, const char *image_path)

{
	BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }
    blit(image, buffer, 0, 0, 56, 338, image->w, image->h);
	
}	

void draw_move_card(BITMAP *buffer, int move_id, int w)
{
	BITMAP  *image = load_pcx(move_list[move_id - 1].icon, NULL);
	    if (!image) {
        allegro_message("Failed to load move icon");
        printf("Loading move %d failed", move_list[move_id].id);
        return;
    }
    rect(buffer, w - 2, 370, image->w + w + 2, image ->h + 370, makecol(0, 0, 0));
    blit(image, buffer, 0, 0, w, 372, image->w, image->h);
    destroy_bitmap(image);
} 
	
void chara_info(BITMAP* buffer, int char_id, int current_hp, int status_id)
{
    const char *chara_name;
    const char *chara_status = "OK"; // Default value if no match is found
    
    // Hardcoded character names
    switch(char_id){
    case 0:
        chara_name = "Yurinka";
        break;
    case 1:
        chara_name = "Markus";
        break;
    case 2:
        chara_name = "Ola";
        break;
    default:
        chara_name = "Unknown";
        break;
    }

    // Search for the status in status_list
    for (int i = 0; i < 9; i++) {
        if (status_list[i].id == status_id) {
            chara_status = status_list[i].name;
            break;
        }
    }

    // Display character info
    textout_ex(buffer, font, chara_name, 178 , 332, makecol(255, 255, 255), -1);
    textout_ex(buffer, font, chara_status, 356 , 332, makecol(255, 255, 255), -1);
}

void display_attack_info(int selection, int character)
{textout_ex(buffer, font, move_list[(selection - 1) + (character * 3)].move_name, 62 , 274, makecol(255, 255, 255), -1);
}

void battle_message(const char *message)

{	draw_superui();
	textout_ex(buffer, font, message, 62 , 274, makecol(255, 255, 255), -1);
	blit(buffer, screen, 58, 270, 58, 270, 490, 40);
	rest(50);
}

void battle_message_row2(const char *message)
{textout_ex(buffer, font, message, 62 , 284, makecol(255, 255, 255), -1);
	blit(buffer, screen, 58, 270, 58, 270, 490, 40);
	rest(50);
}

void display_enemy_choices(int enemy1, int enemy2, int enemy3)
{
  if (enemy1 != 0) {textprintf_ex(buffer, font, 62, 274, makecol(255,255,255) , -1, "Press 1 to attack: %s", foe_list[enemy1].name);
  }
  if (enemy2 != 0) {textprintf_ex(buffer, font, 62, 282, makecol(255,255,255) , -1, "Press 2 to attack: %s", foe_list[enemy2].name);
  }
  if (enemy3 != 0) {textprintf_ex(buffer, font, 62, 288, makecol(255,255,255) , -1, "Press 3 to attack: %s", foe_list[enemy3].name);
	}
}

void display_ally_choices(int ally1, int ally2, int ally3)
{
  if (ally1 != 0) 
  {textprintf_ex(buffer, font, 62, 274, makecol(180,255,255) , -1, "Press 1 to assist: Yurinka");
  }
  if (ally2 != 0) {textprintf_ex(buffer, font, 62, 282, makecol(255,180,255) , -1, "Press 2 to assist: Markus");
  }
  if (ally3 != 0) {textprintf_ex(buffer, font, 62, 288, makecol(180,180,255) , -1, "Press 3 to assist: Ola");
	}
}



void display_choice(int choice)
{textprintf_ex(buffer, font, 61, 377, makecol(255,255,255) , -1, "Current choice: %d", choice);
}

const char* get_hp_status(int current_hp, int max_hp) {
    float percentage = (float)current_hp / (float)max_hp;

    if (percentage <= 0.10) {
        return "CRITICAL";
    } else if (percentage <= 0.25) {
        return "LOW";
    } else if (percentage <= 0.40) {
        return "MID-LOW";
    } else if (percentage <= 0.60) {
        return "MID";
    } else if (percentage <= 0.80) {
        return "MID-HIGH";
    } else if (percentage <= 0.95) {
        return "HIGH";
    } else {
        return "FULL";
    }
}


void draw_hp_bar(BITMAP* buffer, int current_hp, int max_hp, int x, int y, int width, int height) {
    float percentage = (float)current_hp / (float)max_hp;
    int segments = 7;  // We have 7 segments total
    int segment_width = width / segments;
    
    // Assign colors based on segment index (from critical to full HP)
    int colors[7] = {DARK_RED, RED, ORANGE, YELLOW, GREEN, TEAL, BLUE};
    
    // Draw the active segments
    for (int i = 0; i < segments; i++) {
        if (percentage > (float)i / segments) {
            rectfill(buffer, x + (i * segment_width), y, x + ((i + 1) * segment_width), y + height, colors[i]);
        } else {
            // Draw an empty or darkened segment for inactive portions
            rectfill(buffer, x + (i * segment_width), y, x + ((i + 1) * segment_width), y + height, makecol(50, 50, 50));
        }
    }
    
    // Optionally, draw a border around the HP bar
    rect(buffer, x, y, x + width, y + height, makecol(255, 255, 255));
}


void draw_hp_status(BITMAP* buffer, int current_hp, int max_hp, int x, int y) {
    const char* status_text = get_hp_status(current_hp, max_hp);
    
    textout_ex(buffer, font, status_text, x, y, makecol(255, 255, 255), -1);
}

void load_battle_background(BITMAP *buffer, int battle_id)
{
	BITMAP *image = load_pcx(get_battle_background(battle_id), NULL);
	  if (!image) {
        allegro_message("Failed to load image");
        return;
    }
    blit(image, buffer, 0, 0, 54, 18, image->w, image->h);
    // Destroy the image bitmap as it is no longer needed
    destroy_bitmap(image);
    
}

void draw_superui() {
	rectfill(buffer, 58, 270, 548, 310, makecol(0, 0, 120));
	rectfill(buffer, 60, 272, 546, 308, makecol(0, 0, 220));
}
 
void load_battle_foe(BITMAP *buffer, int battle_id, int foe_index, int w)

{	

	BITMAP *image = load_pcx(get_enemy_sprite(foe_index, battle_id), NULL);
    set_trans_blender(255, 0, 255, 0);
    masked_blit(image, buffer, 0, 0, w , 20, image->w, image->h);
    // Destroy the image bitmap as it is no longer needed
    destroy_bitmap(image);    
}
	
	



void draw_battle_ui(BITMAP* buffer, int current_hp, int max_hp, int char_id, int status_id) {
    // Character info (name, status)
    draw_battleui_base(buffer);
    chara_info(buffer, char_id, current_hp, status_id);

    // Draw HP bar
    draw_hp_bar(buffer, current_hp, max_hp, 178, 352, 200, 10);  // Adjust position/size as needed

    // Display vague HP status text
    draw_hp_status(buffer, current_hp, max_hp, 400, 353);
}




void triple_dialog(const char *text1, const char *text2, const char *text3) {
    // Check for null pointers
    if (!text1 || !text2 || !text3) {
        fprintf(stderr, "One or more text arguments are NULL\n");
        return; // Exit the function if any text is NULL
    }

    // Ensure buffer is initialized
    if (!buffer) {
        fprintf(stderr, "Buffer is not initialized\n");
        return; // Exit the function if buffer is NULL
    }

    // Ensure TEXTBOX_WPOS and TEXTBOX_HPOS are valid
    if (TEXTBOX_WPOS < 0 || TEXTBOX_HPOS < 0 || 
        TEXTBOX_WPOS >= SCREEN_W || TEXTBOX_HPOS >= SCREEN_H) {
        fprintf(stderr, "Invalid textbox position\n");
        return; // Exit the function if positions are invalid
    }

    // Draw the dialog box
    rectfill(buffer, 54, 340, 578, 410, makecol(0, 128, 128));
    rect(buffer, 54, 340, 578, 410, makecol(0,0,0));
    // Draws three lines of dialog. Standard way to display text
    textout_ex(buffer, font, text1, TEXTBOX_WPOS, TEXTBOX_HPOS, makecol(255, 255, 255), -1);
    rest(5);
    textout_ex(buffer, font, text2, TEXTBOX_WPOS, TEXTBOX_HPOS + LINE_SPACING, makecol(255, 255, 255), -1);
    rest(5);
    textout_ex(buffer, font, text3, TEXTBOX_WPOS, TEXTBOX_HPOS + (LINE_SPACING * 2), makecol(255, 255, 255), -1);
    rest(5);
    
}

void triple_dialog_typewriter(const char *text1, const char *text2, const char *text3) {
    // Ensure buffer is initialized
    if (!buffer) {
        fprintf(stderr, "Buffer is not initialized\n");
        return;
    }

    // Draw the dialog box
    rectfill(buffer, 54, 340, 578, 410, makecol(50, 50, 200));
    rect(buffer, 54, 340, 578, 410, makecol(0,0,0));

    // Typewriter effect for each line of text
    typewriter_text(buffer, text1, TEXTBOX_WPOS, TEXTBOX_HPOS, makecol(255, 255, 255));
    typewriter_text(buffer, text2, TEXTBOX_WPOS, TEXTBOX_HPOS + LINE_SPACING, makecol(255, 255, 255));
    typewriter_text(buffer, text3, TEXTBOX_WPOS, TEXTBOX_HPOS + (LINE_SPACING * 2), makecol(255, 255, 255));
}

void choice_picker_base(BITMAP *buffer, int n_choices) {
    // Draw choices for branching storyline.
    // Each choice will be a rectangle with spacing between them.
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1)); // Total width for all choices combined
    int choice_width = total_width / n_choices; // Width of each choice box

    // Draw shadow effect for choice boxes
    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + i * (choice_width + CHOICE_SPACING);  // Left edge of the choice box
        int x2 = x1 + choice_width;                                    // Right edge of the choice box
        int y1 = CHOICE_Y_OFFSET;                                      // Top edge of the choice box
        int y2 = y1 + CHOICE_HEIGHT;                                   // Bottom edge of the choice box

        // Draw shadow
        rectfill(buffer, x1 + 3, y1 + 3, x2 + 3, y2 + 3, makecol(0, 0, 0)); // Shadow rectangle
        // Draw the rectangle for the current choice
        rectfill(buffer, x1, y1, x2, y2, CHOICE_COLOR);
        rect(buffer, x1, y1, x2, y2, makecol(0, 0, 0));
    }
}

void choice_picker_text(const char *choice1, const char *choice2, const char *choice3, int n_choices) {
    // Draws text for each choice box
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1)); // Total width for all choices combined
    int choice_width = total_width / n_choices; // Width of each choice box

    // Draw each choice box
    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + 10 + i * (choice_width + CHOICE_SPACING);  // Left edge of the choice box
        int y1 = CHOICE_Y_OFFSET + 5;                                      // Top edge of the choice box

        switch(i)
        {
            case 0:
            textout_ex(buffer, font, choice1, x1 + 1, y1 + 1, makecol(0, 0, 0), -1); // Shadow
            textout_ex(buffer, font, choice1, x1, y1, makecol(0, 0, 0), -1);
            break;
            case 1:
            textout_ex(buffer, font, choice2, x1 + 1, y1 + 1, makecol(0, 0, 0), -1); // Shadow
            textout_ex(buffer, font, choice2, x1, y1, makecol(0, 0, 0), -1);
            break;
            case 2:
            textout_ex(buffer, font, choice3, x1 + 1, y1 + 1, makecol(0, 0, 0), -1); // Shadow
            textout_ex(buffer, font, choice3, x1, y1, makecol(0, 0, 0), -1);
            break;
            default:
            textout_ex(buffer, font, "Out of bounds!", x1 + 1, y1 + 1, makecol(0, 0, 0), -1); // Shadow
            textout_ex(buffer, font, "Out of bounds!", x1, y1, makecol(0, 0, 0), -1);
        }
    }   
}


void load_blit(const char *image_path, BITMAP *buffer, int dst_x, int dst_y) {
    // Load the new image from the specified path
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }

    // Create a temporary buffer for rendering the effect
    BITMAP *temp_buffer = create_bitmap(buffer->w, buffer->h);
    if (!temp_buffer) {
        allegro_message("Failed to create temporary buffer.");
        destroy_bitmap(image);
        return;
    }

    int num_bars = 32; // Number of bars (adjust for more/less bars)
    int bar_height = SCREEN_H / num_bars; // Height of each bar
    int transition_speed = 4; // Speed of transition (lower is faster)

    // Transition effect loop
    for (int step = 0; step <= bar_height; step += transition_speed) {
        // Clear the temporary buffer
        clear(temp_buffer);

        // Loop through each bar
        for (int i = 0; i < num_bars; i++) {
            // For even bars, reveal from top to bottom
            if (i % 2 == 0) {
                masked_blit(image, temp_buffer, 0, i * bar_height, dst_x, dst_y + i * bar_height, image->w, step);
            } 
            // For odd bars, reveal from bottom to top
            else {
                masked_blit(image, temp_buffer, 0, (i + 1) * bar_height - step, dst_x, dst_y + i * bar_height, image->w, step);
            }
        }
		
        // Blit the temp buffer onto the main buffer
        blit(temp_buffer, buffer, 0, 0, 0, 0, buffer->w, buffer->h);

        // Display the buffer on screen
        vsync();  // Ensure smooth transitions
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(20);  // Control the speed of the effect
    }
	draw_dialog_base(buffer);
    // Once the transition is complete, blit the new image fully
    blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // Clean up
    destroy_bitmap(image);
    destroy_bitmap(temp_buffer);
}

void load_blit_alt(const char *image_path, int dst_x, int dst_y) {
    // Load the new image from the specified path
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }

    // Create a temporary buffer for rendering the effect
    BITMAP *temp_buffer = create_bitmap(buffer->w, buffer->h);
    if (!temp_buffer) {
        allegro_message("Failed to create temporary buffer.");
        destroy_bitmap(image);
        return;
    }

    int num_bars = 32; // Number of bars (adjust for more/less bars)
    int bar_height = SCREEN_H / num_bars; // Height of each bar
    int transition_speed = 4; // Speed of transition (lower is faster)

    // Transition effect loop
    for (int step = 0; step <= bar_height; step += transition_speed) {
        // Clear the temporary buffer
        clear(temp_buffer);

        // Loop through each bar
        for (int i = 0; i < num_bars; i++) {
            // For even bars, reveal from top to bottom
            if (i % 2 == 0) {
                masked_blit(image, temp_buffer, 0, i * bar_height, dst_x, dst_y + i * bar_height, image->w, step);
            } 
            // For odd bars, reveal from bottom to top
            else {
                masked_blit(image, temp_buffer, 0, (i + 1) * bar_height - step, dst_x, dst_y + i * bar_height, image->w, step);
            }
        }
		
        // Blit the temp buffer onto the main buffer
        blit(temp_buffer, buffer, 0, 0, 0, 0, buffer->w, buffer->h);

        // Display the buffer on screen
        vsync();  // Ensure smooth transitions
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(20);  // Control the speed of the effect
    }
	draw_dialog_base(buffer);
    // Once the transition is complete, blit the new image fully
    blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // Clean up
    destroy_bitmap(image);
    destroy_bitmap(temp_buffer);
}


void load_blit_transparent(const char *image_path, BITMAP *buffer, int dst_x, int dst_y) {
    // Load the image from the specified path
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }

    // Use masked_blit to draw the image with transparency
    masked_blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);

    // Destroy the image bitmap as it is no longer needed
    destroy_bitmap(image);
}


