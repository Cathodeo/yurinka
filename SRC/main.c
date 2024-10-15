#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <draw.h>
#include <parse.h>
#include <music.h>
#include <room.h>

#define TEXTBOX_WPOS 58
#define TEXTBOX_HPOS 344
#define TEXTBOX_WIDTH 300

int main(void) {
    int current_file = 1;
    int type_gp = 1;
    int text_scroll = 1;
    int choice = 0;
    int current_room_id = 1;
    int newroom = 1;
    int room_compare = 1;
    int gamemode_change = 1;
    int text_updated = 0; // Track if the text has been updated
    int switches = 0;

    // Define arrays to hold text and choices
    char textlines[3][64];
    char choices[3][16];
    char imagename[64];
    char musicname[64];
    char roomfile[16];
    char sfxfile[64]; 
    char ambiancefile[64];
    int line_numbers[6] = {1, 2, 3, 4, 5, 6}; // Initialize line_numbers array
    int size = sizeof(line_numbers) / sizeof(line_numbers[0]); // Size of line_numbers

	
    Room current_room;
    int room_tracker = 1;
   

    allegro_init();
    install_timer();
    set_color_depth(16);
    if (set_gfx_mode(GFX_SAFE, 640, 480, 0, 0) != 0) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
        return 1;
    }

    install_keyboard();
    
    initialize_sdl_mixer();
	Mix_VolumeMusic(48);
	

    set_trans_blender(255, 0, 255, 0);
    chdir("/home/tmmartin/YURINKA");



    // Initialize the file pointer and check for successful opening
    FILE *file = fopen("STORY/001A.TXT", "r");
    if (!file) {
        allegro_message("Failed to open STORY/001A.TXT");
        return 1;
    }



    // Create a buffer
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Failed to create buffer!");
        return -1;
    }

    draw_dialog_base(buffer);
    choice_picker_base(buffer, 3);
    load_blit("IMG/BAL001.PCX", buffer, 54, 18);


    // Main game loop
    while (!key[KEY_ESC]) {
    // Change between gameplays or stay the same (type_gp is a fallback that contains the last value stored)
    switch (type_gp) {
        case 1:
            type_gp = parse_vnmode(text_updated, text_scroll, size, file, line_numbers, textlines, choices, imagename, musicname, sfxfile, ambiancefile);
            break;

       case 2:
    while(type_gp == 2) {
    if (newroom == 1) { // When entering a new room
   
        printf("\nLoading room: %d", room_tracker);  // Note: changed \n to \n for new line
        install_mouse();
        poll_mouse();
        enable_hardware_cursor();
        show_mouse(screen);
        // Load room objects and initialize the room
        current_room = getRoomObjects(room_tracker);
        current_room.room_id = room_tracker;

        // Open the correct file for the room
        fclose(file); // Close the previous file
        strcpy(roomfile, get_room_txt_file(room_tracker));
        file = fopen(roomfile, "r");

        if (!file) {
            allegro_message("Failed to open room file: %s", roomfile);
            return 1;
        }

        // Initialize line_numbers for text
        for (int i = 1; i < 7; i++) {
            line_numbers[i - 1] = i;
        }
		
        // Parse room-specific information
        text_roll(file, line_numbers, textlines, choices, imagename, musicname, sfxfile, ambiancefile);
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		rest(50);
        // After loading the new room, set `newroom` to 0 to start the interaction loop
        newroom = 0;
        room_compare = room_tracker;
        if (room_tracker == 5)
        {switches = 1;}
    }

    // Main room interaction loop
    while (newroom == 0) {
        poll_mouse();

        // Check for mouse hovering over objects
        int hovered_room = check_hover(current_room, mouse_x, mouse_y, switches);

        // If `hovered_room` has changed, update `room_tracker`
        if (hovered_room != room_tracker) {
            room_tracker = hovered_room;
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); // Redraw background and UI
        }

        // If a room transition is detected, break out of the loop
        if (room_compare != room_tracker && room_tracker != 7) {
            newroom = 1;
            break;
        }
        if (hovered_room == 7)
        {
		fclose(file); // Close the previous file
		FILE *file = fopen("STORY/002A.TXT", "r");
		if (!file) {
		for (int i = 1; i < 7; i++) {
            line_numbers[i - 1] = i;
        }
        allegro_message("Failed to open STORY/002A.TXT");}
        load_blit("IMG/MOT001.PCX", buffer, 54, 18);
        type_gp = 1;
        break;
        }

        rest(5); // Add delay to avoid overloading the CPU
    }
	}
    break;
}

}


    destroy_bitmap(buffer); // Clean up the buffer
    fclose(file); // Ensure the file is closed properly
    allegro_exit(); // Clean up Allegro
    return 0; // Ensure the function ends correctly
}

END_OF_MAIN();
