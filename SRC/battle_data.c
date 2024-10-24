#include <battle_data.h>

Character character_list[] = {
	 {0, 60, 0, 55, 60, 100, 100, {1, 2, 3}, {0, 0}},
	 {1, 120, 0, 80, 99, 60, 120, {4, 5, 6}, {0, 0}},
	 {2, 85, 0, 110, 80, 140, 80, {7, 8, 9}, {0, 0}}, 
};
Foe foe_list[] = {
	{0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "NULL"},
	{1, 60, 140, 80, 100, 100, 0, {10, 10, 10, 10, 10, 11, 11, 11, 12, 12}, "IMG/FOE001.PCX"}
};

Equipable equipable_list[] = {
};

Battle battle_list[] = {
 {0, "IMG/BATT01.PCX", {1, 0, 1}} 
};

Move move_list[] = {
    {1, 25, "Overvoltage", "IMG/MOV001.PCX", 0.9, 0, 1, 30},      // Deals damage, chance to apply "Overheated" status
    {2, 0, "Radio Kill", "IMG/MOV002.PCX", 1.0, 0, 2, 100},      // Reduces enemy evasion by jamming signals
    {3, 0, "Corrupt Memory", "IMG/MOV003.PCX", 0.95, 0, 3, 50},  // Reduces enemy accuracy by corrupting their systems
    {4, 0, "Bodyguard", "IMG/MOV004.PCX", 1.0, 1, 4, 100},       // Redirects attacks to the user, buffs defense
    {5, 40, "Naked Choke", "IMG/MOV005.PCX", 0.8, 0, 5, 20},     // Deals physical damage, chance to disable the target's attack
    {6, 0, "First Aid", "IMG/MOV006.PCX", 1.0, 1, 0, 0},         // Heals ally, no status effect
    {7, 60, "Magic Zapper", "IMG/MOV007.PCX", 0.85, 0, 6, 40},   // Strong zap, chance to paralyze target
    {8, 90, "ElastoPunch", "IMG/MOV008.PCX", 0.75, 0, 0, 0},     // Strong physical punch, no status effect
    {9, 50, "Pocket Drill", "IMG/MOV009.PCX", 0.9, 0, 7, 25},    // Pierces armor, chance to reduce enemy defense
    {10, 60, "Hornet Gun", "IMG/MOV010.PCX", 0.8, 0, 8, 15},     // Fires multiple rounds, chance to poison target
    {11, 0, "Thermal Scan", "IMG/MOV011.PCX", 1.0, 0, 7, 100},   // Scans enemy, lowers their defense
    {12, 0, "Magnetic Shield", "IMG/MOV012.PCX", 1.0, 1, 0, 0}   // Buffs defense, protects against projectile attacks
};


Status status_list[] = {
    {1, "Overheated", 1, 2, 100, 0, 0, 0, 0, 5, 0, 0, 0, 0},         // Causes damage over time (DoT) due to system overheating
    {2, "No Radio", 0, 3, 100, 0, 0, 0, 1, 0, 0, 0, 0, 0},           // Prevents ally targeted attacks.
    {3, "Corrupted", 0, 3, 100, 0, 0, 0, 0, 0, 0, -50, 0, 0},        // Decreases accuracy due to system corruption
    {4, "Shielded", 2, 2, 100, 0, 0, 1, 0, 0, 0, 0, 0, 10},          // Redirects attack to user, buffs defense
    {5, "Choked", 1, 1, 50, 1, 0, 0, 0, 0, 0, 0, 0, 0},              // Prevents attack (disabling due to a chokehold)
    {6, "Paralyzed", 1, 1, 30, 1, 0, 0, 0, 0, 0, 0, 0, 0},           // Prevents attack due to electrical paralysis
    {7, "Armor Shredded", 0, 3, 100, 0, 0, 0, 0, 0, 0, 0, -10, 0},   // Decreases defense due to armor damage
    {8, "Poisoned", 0, 5, 100, 0, 0, 0, 0, 5, 0, 0, 0, 0},           // Deals damage over time (DoT) due to poison
    {9, "Evasion Down", 0, 2, 100, 0, 0, 0, 0, 0, -50, 0, 0, 0},       // Reduces enemy evasion
};
