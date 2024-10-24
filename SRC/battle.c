#include <battle.h>
#include <battle_data.h>


//Functions to draw the attack options

const char* get_battle_background(int battle_id)
{
	return battle_list[battle_id].battle_background;
}


int* get_enemy_party(int battle_id)
{
	return battle_list[battle_id].enemy_list;
}

int get_enemy_id(int index, int battle_id)

{ int* party_ids = get_enemy_party(battle_id);
	return party_ids[index];
}

const char* get_enemy_sprite(int index, int battle_id)
{
	int* party_ids = get_enemy_party(battle_id);
	int foe_id = party_ids[index];
	return foe_list[foe_id].sprite;
}


int* get_base_moves(int character_id) {
	return character_list[character_id].moveset_base;
}


const char* get_movename(int move_id) {
	return move_list[move_id].move_name;
}

int get_move_selection(int index, int character_id) {
	int* base_moves = get_base_moves(character_id);
	return base_moves[index];
}

const char* get_move_icon(int index, int character_id)
{
	int* base_moves = get_base_moves(character_id);
	int move_id = base_moves[index];
	return move_list[move_id].icon;
}

//rect(buffer, w - 2, 370, image->w + w + 2, image ->h + 370,) ;
// 180 + (i * 72)
// Image = 64x64

int mouseCardHover(int mouse_x, int mouse_y) {
	
	int image_xy = 64;
	int offset = 8;
		
    if (mouse_x >= 180 && mouse_x <= (180 + image_xy) &&
        mouse_y >= 370 && mouse_y <= (370 + image_xy)) {
        return 1;  // Hover above card 1
    }
     if (mouse_x >= (180 + offset) && mouse_x  <= (180 + (image_xy * 2)+ offset) &&
        mouse_y >= 370 && mouse_y <= (370 + image_xy)) {
        return 2;  // Hover above card 2
    }
     if (mouse_x >= (180 + (image_xy * 2) + (offset * 2)) && mouse_x <= (180 + (image_xy * 3) + (offset * 2)) &&
        mouse_y >= 370 && mouse_y <= (370 + image_xy)) {
        return 3;  // Hover above card 3
    }
    return 0;  // Mouse is not hovering
}

int moveSelection(int character)

{	int selection;
	selection = mouseCardHover(mouse_x, mouse_y);
	if (selection > 0)
	{
	display_attack_info(selection, character);
	if (key[KEY_ENTER])
	 {return selection;}
	 return 0;
	}
	return 0;
}

