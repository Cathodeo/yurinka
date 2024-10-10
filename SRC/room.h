#ifndef ROOM_H
#define ROOM_H

#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <draw.h>
#include <parse.h>


typedef struct {
	int x;
	int y;
	int width;
	int height;
	int object_id;
} Object;

typedef struct {
    int room_id;   // The unique ID for the room
    Object objects[3]; // Up to 3 objects in each room
} Room;


const char* get_room_txt_file(int current_room);
Room getRoomObjects(int room_id);
int isMouseHovering(int mouse_x, int mouse_y, Object obj);
int check_hover(Room room, int mouse_x, int mouse_y, int switches);
void hoverText(int room_id, int object_id);
int execute_pnc_action(int room_id, int object_id, int switches);
#endif
