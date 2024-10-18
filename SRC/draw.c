// draw.c
#include <draw.h>
#include <math.h>

#define LINE_SPACING 20
#define TEXTBOX_WPOS 58
#define TEXTBOX_HPOS 354
#define TEXTBOX_WIDTH 524
#define CHOICE_HEIGHT 30
#define CHOICE_Y_OFFSET 420
#define CHOICE_SPACING 10

// Define a color scheme
#define BACKGROUND_COLOR makecol(15, 94, 110)
#define DIALOG_BOX_COLOR makecol(25, 64, 79)
#define DIALOG_BORDER_COLOR makecol(255, 255, 255)
#define TEXT_COLOR makecol(255, 255, 255)
#define CHOICE_COLOR makecol(144, 146, 145)
#define BORDER_COLOR makecol(0, 0, 0)

// Helper to draw rounded rectangles
void rounded_rectfill(BITMAP* buffer, int x1, int y1, int x2, int y2, int color) {
    rectfill(buffer, x1 + 5, y1, x2 - 5, y2, color);  // Horizontal part
    rectfill(buffer, x1, y1 + 5, x2, y2 - 5, color);  // Vertical part
    circlefill(buffer, x1 + 5, y1 + 5, 5, color);     // Top-left corner
    circlefill(buffer, x2 - 5, y1 + 5, 5, color);     // Top-right corner
    circlefill(buffer, x1 + 5, y2 - 5, 5, color);     // Bottom-left corner
    circlefill(buffer, x2 - 5, y2 - 5, 5, color);     // Bottom-right corner
}

void draw_dialog_base(BITMAP* buffer) {
    // Clear screen and fill with a dark background
    rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, BACKGROUND_COLOR);

    // Add a layered rectangle with a gradient effect for the dialog box
    for (int i = 0; i < 20; i++) {
        rect(buffer, 54 - i, 16 - i, 572 + i, 322 + i, makecol(25 + i, 64 + i, 79 + i));  // Subtle gradient
    }

    // Draw dialog background with rounded borders
    rounded_rectfill(buffer, 54, 340, 578, 410, DIALOG_BOX_COLOR);
    rect(buffer, 54, 340, 578, 410, DIALOG_BORDER_COLOR);  // Border in white for contrast
}

void triple_dialog(const char *text1, const char *text2, const char *text3) {
    // Check for null pointers
    if (!text1 || !text2 || !text3) {
        fprintf(stderr, "One or more text arguments are NULL\n");
        return;
    }


    // Draw the text with a shadow effect to give depth
    textout_ex(buffer, font, text1, TEXTBOX_WPOS + 2, TEXTBOX_HPOS + 2, makecol(0, 0, 0), -1);  // Shadow
    textout_ex(buffer, font, text1, TEXTBOX_WPOS, TEXTBOX_HPOS, TEXT_COLOR, -1);               // Main text
    rest(5);
    textout_ex(buffer, font, text2, TEXTBOX_WPOS + 2, TEXTBOX_HPOS + LINE_SPACING + 2, makecol(0, 0, 0), -1);  // Shadow
    textout_ex(buffer, font, text2, TEXTBOX_WPOS, TEXTBOX_HPOS + LINE_SPACING, TEXT_COLOR, -1);               // Main text
    rest(5);
    textout_ex(buffer, font, text3, TEXTBOX_WPOS + 2, TEXTBOX_HPOS + (LINE_SPACING * 2) + 2, makecol(0, 0, 0), -1);  // Shadow
    textout_ex(buffer, font, text3, TEXTBOX_WPOS, TEXTBOX_HPOS + (LINE_SPACING * 2), TEXT_COLOR, -1);               // Main text
    rest(5);
}

void choice_picker_base(BITMAP *buffer, int n_choices) {
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1));
    int choice_width = total_width / n_choices;

    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + i * (choice_width + CHOICE_SPACING);
        int x2 = x1 + choice_width;
        int y1 = CHOICE_Y_OFFSET;
        int y2 = y1 + CHOICE_HEIGHT;

        // Draw a rounded rectangle for each choice
        rounded_rectfill(buffer, x1, y1, x2, y2, CHOICE_COLOR);
        rect(buffer, x1, y1, x2, y2, BORDER_COLOR);
    }
}

void choice_picker_text(const char *choice1, const char *choice2, const char *choice3, int n_choices) {
    int i;
    int total_width = TEXTBOX_WIDTH - (CHOICE_SPACING * (n_choices - 1));
    int choice_width = total_width / n_choices;

    for (i = 0; i < n_choices; i++) {
        int x1 = TEXTBOX_WPOS + 10 + i * (choice_width + CHOICE_SPACING);
        int y1 = CHOICE_Y_OFFSET + 10;

        // Display each choice text without any interaction
        switch(i) {
            case 0:
                textout_ex(buffer, font, choice1, x1, y1, makecol(30, 30, 30), -1);
                break;
            case 1:
                textout_ex(buffer, font, choice2, x1, y1, makecol(30, 30, 30), -1);
                break;
            case 2:
                textout_ex(buffer, font, choice3, x1, y1, makecol(30, 30, 30), -1);
                break;
            default:
                textout_ex(buffer, font, "Out of bounds!", x1, y1, makecol(30, 30, 30), -1);
        }
    }
}

void load_blit(const char *image_path, BITMAP *buffer, int dst_x, int dst_y) {
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }
    blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);
    destroy_bitmap(image);
}

void load_blit_transparent(const char *image_path, BITMAP *buffer, int dst_x, int dst_y) {
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }
    masked_blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);
    destroy_bitmap(image);
}
