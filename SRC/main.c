#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <draw.h>
#include <parse.h>
#include <music.h>
#include <room.h>
#include <battle.h>
#include <battle_data.h>

#define TEXTBOX_WPOS 58
#define TEXTBOX_HPOS 344
#define TEXTBOX_WIDTH 300


int is_self(int allyup, int index_self, int index_allypos)
{
	if (allyup == 0)
	{return 0;}
	if (index_self == index_allypos)
	{return 0;}
	else
	{return 1;}
	
}




int main(void) {
	


	int selection = 0;
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
    
    //Battle stuff
    
  
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
	Battle_Tracker tracker;
    tracker.rotation = 0;
    tracker.ready = 0;
    int battle_id = 0;
    int max_hp = character_list[tracker.rotation].health;
    int current_hp = max_hp;
    int status;
    int char_id;
    int status_id;
    int current_target = 0;
    int party_battle_selections[3];
    int foe_target_selection[3];
    int ally_up[3];

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
			 while (!key[KEY_ENTER] && type_gp == 1) {
                            rest(20);
                        }
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
    
    
    case 3:
    
    ally_up[0] = 1;
    ally_up[1] = 2;
    ally_up[2] = 3;
    install_mouse();
    poll_mouse();
    enable_hardware_cursor();
    show_mouse(screen);
    selection = 0;
    //Draw battle UI and render the background
    draw_battleui_base(buffer);
    draw_battle_ui(buffer, current_hp, max_hp, tracker.rotation, status);
    load_battle_background(buffer, battle_id);	
    printf("Debug: Drawing graphical elements finished");
    //Init group of enemies
    
    //Init with three enemy ids.
    //For all practical purpose, the enemy with id 0
    //Is not rendered or considered alive
    int enemy_party_id[3];
    Foe enemy_party[3];
    for (int i = 0; i < 3; i++)
    {
    enemy_party_id[i] = get_enemy_party(battle_id)[i];
    enemy_party[i] = foe_list[enemy_party_id[i]];
    //If the enemy id on the party is not 0
	//(Not empty), initialize as up (alive)
		if (enemy_party_id[i] > 0)
		{
		 tracker.foe_up[i] = 1;
		 load_battle_foe(buffer, battle_id, i, (40 + (120 * i)));
		}
	}
	printf("Debug: Loaded enemy party, drawn enemy foes");
    switch (tracker.rotation)
    {
	case 0:
    draw_portrait(buffer, "IMG/FACE1.PCX");
    break;
    case 1:
    draw_portrait(buffer, "IMG/FACE3.PCX");
    break;
	case 2:
    draw_portrait(buffer, "IMG/FACE2.PCX");
    break;
	}
	printf("Debug: Loaded portrait");
	//Debug. To expand!
	for (int i = 0; i < 3; i++) {
	draw_move_card(buffer, character_list[tracker.rotation].moveset_base[i], 180 + (i * 72));
	}
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    while (selection == 0)
	{
	poll_mouse();
	selection = moveSelection(tracker.rotation);
	printf("Executed selection checker with result: %d \n", selection);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	rest(10);
	}
	while (current_target == 0)
	{
		if (is_move_ally_targeted(selection, tracker.rotation) == 1)
		{current_target = choiceShow_ally(
		is_self(ally_up[0], tracker.rotation, 0),
		is_self(ally_up[1], tracker.rotation, 1),
		is_self(ally_up[2], tracker.rotation, 2)
		);
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		rest(20);}
		else {
		current_target = choiceShow(enemy_party_id[0], enemy_party_id[1], enemy_party_id[2]);
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		rest(20);}
	}					
						
						foe_target_selection[tracker.rotation] = current_target;
						party_battle_selections[tracker.rotation] = selection;
                        rest(50);
						if (tracker.rotation < 2)
						{tracker.rotation++;}
						else
						{tracker.rotation = 0;}
						status = character_list[tracker.rotation].health;
						draw_battleui_base(buffer);
                        draw_battle_ui(buffer, current_hp, max_hp, tracker.rotation, status);
						status_id = character_list[tracker.rotation].status;
						switch (tracker.rotation)
						{
						case 0:
						draw_portrait(buffer, "IMG/FACE1.PCX");
						break;
						case 1:
						draw_portrait(buffer, "IMG/FACE3.PCX");
						break;
						case 2:
						draw_portrait(buffer, "IMG/FACE2.PCX");
						break;
						}
						printf("Debug: Loaded portrait");
						//Debug. To expand!
						for (int i = 0; i < 3; i++) {
						draw_move_card(buffer, character_list[tracker.rotation].moveset_base[i], 180 + (i * 72));
						}
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						selection = 0;
						current_target = 0;
                        rest(100);
    break;
    
}

}


    destroy_bitmap(buffer); // Clean up the buffer
    fclose(file); // Ensure the file is closed properly
    allegro_exit(); // Clean up Allegro
    return 0; // Ensure the function ends correctly
}

END_OF_MAIN();
