// draw.c
#include <draw.h> 
#include <math.h>

#define LINE_SPACING 20     
#define TEXTBOX_WPOS 58
#define TEXTBOX_HPOS 354 
#define TEXTBOX_WIDTH 524
#define CHOICE_HEIGHT 20
#define CHOICE_Y_OFFSET 420
#define CHOICE_COLOR makecol(144, 146, 145)
#define CHOICE_SPACING 10

void draw_dialog_base(BITMAP* buffer) {
    // Clear screen and fill background with teal color
    rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(30, 120, 108));  // Teal background
    // Draw a smaller rectangle inside the screen bounds
    rectfill(buffer, 54, 18, 578, 320, makecol(25, 64, 59));  // Darker rectangle
    rectfill(buffer, 54, 340, 578, 410, makecol(144, 146, 145));
    rect(buffer, 54, 340, 578, 410, makecol(0,0,0));
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
    rectfill(buffer, 54, 340, 578, 410, makecol(144, 146, 145));
    rect(buffer, 54, 340, 578, 410, makecol(0,0,0));
    // Draws three lines of dialog. Standard way to display text
    textout_ex(buffer, font, text1, TEXTBOX_WPOS, TEXTBOX_HPOS, makecol(255, 255, 255), -1);
    rest(5);
    textout_ex(buffer, font, text2, TEXTBOX_WPOS, TEXTBOX_HPOS + LINE_SPACING, makecol(255, 255, 255), -1);
    rest(5);
    textout_ex(buffer, font, text3, TEXTBOX_WPOS, TEXTBOX_HPOS + (LINE_SPACING * 2), makecol(255, 255, 255), -1);
    rest(5);
    
}


void choice_picker_base(BITMAP *buffer, int n_choices) {
    // Draws choices for branching storyline.
    // Each choice will be a rectangle with spacing between them.
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1)); // Total width for all choices combined
    int choice_width = total_width / n_choices; // Width of each choice box

    // Draw each choice box
    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + i * (choice_width + CHOICE_SPACING);  // Left edge of the choice box
        int x2 = x1 + choice_width;                                    // Right edge of the choice box
        int y1 = CHOICE_Y_OFFSET;                                      // Top edge of the choice box
        int y2 = y1 + CHOICE_HEIGHT;                                   // Bottom edge of the choice box

        // Draw the rectangle for the current choice
        rectfill(buffer, x1, y1, x2, y2, CHOICE_COLOR);
        rect(buffer, x1, y1, x2, y2, makecol(0, 0, 0));
    }
}

void choice_picker_text(const char *choice1, const char *choice2, const char *choice3, int n_choices) {
    // Draws choices for branching storyline.
    // Each choice will be a rectangle with spacing between them.
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1)); // Total width for all choices combined
    int choice_width = total_width / n_choices; // Width of each choice box

    // Draw each choice box
    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + 10 + i * (choice_width + CHOICE_SPACING);  // Left edge of the choice box                                // Right edge of the choice box
        int y1 = CHOICE_Y_OFFSET + 5;                                      // Top edge of the choice box                                  // Bottom edge of the choice box

        switch(i)
        {
            case 0:
            textout_ex(buffer, font, choice1, x1, y1, makecol(0, 0, 0), -1);
            break;
            case 1:
            textout_ex(buffer, font, choice2, x1, y1, makecol(0, 0, 0), -1);
            break;
            case 2:
            textout_ex(buffer, font, choice3, x1, y1, makecol(0, 0, 0), -1);
            break;
            default:
            textout_ex(buffer, font, "Out of bounds!", x1, y1, makecol(0, 0, 0), -1);
        }
    }   

}

void load_blit(const char *image_path, BITMAP *buffer, int dst_x, int dst_y) {
    // Load the image from the specified path
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }

    // Blit the image onto the buffer at the specified position
    blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);

    // Destroy the image bitmap as it is no longer needed
    destroy_bitmap(image);
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


