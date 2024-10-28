#include <battle.h>
#include <battle_data.h>


void init_rng() {
    srand(time(NULL));
}

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

int is_move_ally_targeted(int selection, int character_id)
{
	int move_id = (character_list[character_id].moveset_base[selection - 1] - 1);
	if (move_list[move_id].is_ally_target == 0)
	{return 0;}
	if (move_list[move_id].is_ally_target == 1)
	{return 1;}
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
	printf("Mouse pos is %d for x, %d for y \n", mouse_x, mouse_y);
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
	draw_superui();
	display_attack_info(selection, character);
	if (key[KEY_ENTER])
	 {return selection;}
	 return 0;
	}
	draw_superui();
	return 0;
}

int choiceShow(int enemy_1, int enemy_2, int enemy_3)
{
	draw_superui();
	display_enemy_choices(enemy_1, enemy_2, enemy_3);
	if (key[KEY_1]) 
	{return 1;}
	if (key[KEY_2])
	{return 2;}
	if (key[KEY_3])
	{return 3;}
	return 0;
	
}

int choiceShow_ally(int ally_1, int ally_2, int ally_3)
{draw_superui();
 display_ally_choices(ally_1, ally_2, ally_3);
 	if (key[KEY_1]) 
	{return 1;}
	if (key[KEY_2])
	{return 2;}
	if (key[KEY_3])
	{return 3;}
	return 0;
} 


///Battle processing

int get_attacker_damage(int attacking_part, int isfoe)
{
	if (isfoe == 1)
	{
		return foe_list[attacking_part].attack;
	}
	if (isfoe == 0)
	{
		return character_list[attacking_part].attack;
	}
}

int get_defender_damage(int defending_part, int isfoe)
{
	if (isfoe == 1)
	{
	return foe_list[defending_part].defense;
	}
	if (isfoe == 0)
	{
	return character_list[defending_part].defense;
	}
}

int calculate_damage(int attack_power, int base_power, int defense) {
    float random_factor = 0.9f + (rand() % 21) / 100.0f; // Random factor between 0.9 and 1.1
    int damage = (int)((attack_power * base_power / (float)defense) * random_factor);
    return damage > 0 ? damage : 1; // Ensures minimum damage of 1
}


int check_status_condition(int chara_foe, int actor_id) {
    // Retrieve status condition (0 = can act, 1 = paralyzed, etc.)
    int status = get_character_status(actor_id);
    if (status == 1) { // Example: 1 could mean "paralyzed"
        int roll = rand() % 100;
        if (roll < 50) { // 50% chance that paralysis prevents action
            return 0;
        }
    }
    // Add other status checks here as needed
    return 1;
}

// Checks if the attack lands based on accuracy and character's accuracy multiplier
int check_accuracy(int chara_foe, int actor_id, int move_id, int battle_id) {
	float accuracy_multiplier;
    int base_accuracy = (move_list[move_id].accuracy_multiplier) * 100;
     
     if (chara_foe == 0)
    {accuracy_multiplier = (foe_list[battle_list[battle_id].enemy_list[actor_id]].accuracy / 100);}  // e.g., 1.2 for 120% accuracy
    if (chara_foe == 1)
    {accuracy_multiplier = get_accuracy_multiplier(character_list[actor_id].accuracy / 100);}
    int effective_accuracy = (int)(base_accuracy * accuracy_multiplier);
    int roll = rand() % 100;
    return roll < effective_accuracy; // 1 if hit, 0 if miss
}

// Checks if a secondary effect is applied based on the move's effect chance
int check_special_effects(int move_id) {
    int effect_chance = get_move_effect_chance(move_id); // e.g., 30 for 30% chance
    int roll = rand() % 100;
    
    return roll < effect_chance; // 1 if effect applies, 0 if not
}



