// battle.h
#ifndef BATTLE_H
#define BATTLE_H

#include <allegro.h>

typedef struct {
    int id;         // Character ID
    int health;
    int attack; 
    int variability;
    int crit;         
    int speed; 
    int status;
    int accuracy;
    int evasion;
    int defense;
    int moveset_base[3];
    int equipped[2];
} Character;


typedef struct {
	int id;
	int health;
	int attack;
	int speed;
	int accuracy;
	int evasion;
	int defense;
	int status;
	int moveset[10];
	char sprite[16];
	char name[24];
} Foe;


typedef struct {
	int id;
	int equipable;
	int equipable_to[3];
	int move_granted_id;
	int stats_up[5];
} Equipable;

typedef struct {
	int id;
	int power;
	char move_name[24];
	char icon[16];
	float accuracy_multiplier;
	int is_ally_target;
	int status;
	int status_chance;
} Move;

typedef struct {
	int id;
	char name[16];
	int remove_condition;
	int remove_turns;
	int remove_chance;
	int prevents_attack;
	int redirects_attack;
	int redirects_target;
	int prevents_ally_target;
	int dot_amount;
	int evasion_debuff;
	int accuracy_debuff;
	int defense_debuff;
	int defense_buff;
} Status;


typedef struct {
	int id;
	char battle_background[16]; 
	int enemy_list[3];  
} Battle;

typedef struct {
	int item_ids[6];
} Inventory;

typedef struct {
	int rotation;
	int ready;
	int foe_up[3];
	int ally_up[3];
	int hp_track[2][3];
	int status_track[2][3];
	int current_deck[3][5];
	int choices[2][3];
	} Battle_Tracker;
	
typedef struct {
 char line1_execution[64];
 char line2_execution[64];
 char hit[64];
 char miss1[64];
 char miss2[64];
 char miss3[64];
} Move_Messages;


void init_rng();
int* populate_individual_deck(int chara_id); //New
int* get_enemy_party(int battle_id); 
int get_enemy_id(int index, int battle_id);
const char* get_enemy_sprite(int index, int battle_id);
int* get_base_moves(int character_id);         // Get available moves for a character
int* get_enemy_party(int battle_id);
const char* get_battle_background(int battle_id);
const char* get_movename(int move_id);
const char* get_move_icon(int index, int character_id);
int selection_track_mouse(int mouse_x, int mouse_y); //New
int get_move_selection(int index, int character_id);
int mouseCardHover(int mouse_x, int mouse_y);
int moveSelection(int character);
int choiceShow(int enemy_1, int enemy_2, int enemy_3);
int choiceShow_ally(int ally_1, int ally_2, int ally_3);
int is_move_ally_targeted(int selection, int character_id);

//Main battle processing
//
//
int check_status_condition(int chara_foe, int actor_id);
int check_accuracy(int chara_foe, int actor_id, int move_id);
int check_special_effects(int move_id);
int apply_damage_target(int attacker_id, int defender_id, int base_power, int is_multi, int multiplier, int crit_chance);


#endif
