#include <battle_data.h>


Frame frame_list[] = {
	{"IMG/YURBA1.PCX"},
	{"IMG/MARBA1.PCX"},
	{"IMG/OLABA1.PCX"},
	{},
	{},
	{},
	{"IMG/FOEBA1.PCX"}
};

Character character_list[] = {
    {0, 60, 70, 55, 2, 1, 0, 85, 100, 100, {1, 2, 3}, {0, 0}},
    {1, 120, 90, 80, 1, 0, 0, 99, 60, 120, {4, 5, 6}, {0, 0}},
    {2, 85, 100, 110, 4, 3, 80, 95, 80, 100, {7, 8, 9}, {0, 0}} 
};


Foe foe_list[] = {
	{0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "NULL", "None"},
	{1, 60, 55, 140, 80, 100, 100, 0, {10, 10, 10, 10, 10, 11, 11, 11, 12, 12}, "IMG/FOE001.PCX", "Mechanical Hornet"}
};

Equipable equipable_list[] = {
};

Battle battle_list[] = {
 {0, "IMG/BATT01.PCX", {1, 0, 1}, 0, 1, 2, {6,6,6}} 
};

Move move_list[] = {
    {1, 25, "Overvoltage", "IMG/MOV001.PCX", 0.9, 0, 1, 30},      // Deals damage, chance to apply "Overheated" status
    {2, 0, "Radio Kill", "IMG/MOV002.PCX", 1.0, 0, 2, 100},      // Reduces enemy evasion by jamming signals
    {3, 0, "Corrupt Memory", "IMG/MOV003.PCX", 0.95, 0, 3, 50},  // Reduces enemy accuracy by corrupting their systems
    {4, 0, "Bodyguard", "IMG/MOV004.PCX", 1.0, 1, 4, 100},       // Redirects attacks to the user, buffs defense
    {5, 40, "Naked Choke", "IMG/MOV006.PCX", 0.8, 0, 5, 20},     // Deals physical damage, chance to disable the target's attack
    {6, 0, "First Aid", "IMG/MOV005.PCX", 1.0, 1, 0, 0},         // Heals ally, no status effect
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


Move_Messages message_list[] =


{
	{"Yurinka attempted to adjust the enemy's electronics","to a dangerous level of voltage.",
		"The foe's electronics are boiling hot!",
		"She misplaced a comma. The enemy's voltage rebooted",
		"Her code did not even compile. Check the syntax",
		"The foe is still on its safe range of temperatures!"}
		,
	{"Yurinka attempted to inhibit the radio", "signal on the target foe",
		"The foe's signals have been shut down!",
		"Only the frequency of Discopolo Radio was inhibited.",
		"Yurinka used AM instead of FM so nothing happened",
		"Her portable radio ran out of AAA batteries. Oops."}
		,
	{"Yurinka messed up the foe memory", "with gibberish data",
	"The enemy's systems are corrupted!",
	"THAT region of memory was unused tho...",
	"Yurinka forgot a semicolon. Her code did not compile!",
	"Yurinka got distracted playing BOOM on her radio"}
	,
	{"Markus tried to protect his teammate", "Against the enemy attacks"
	 "Markus is body-blocking attacks now!",
	 "Markus tripped on an obstacle on its way",
	 "Markus got distracted by a trivial order from Yurinka",
	 "Markus's sunglasses were to dirty to locate his ally"}
	 ,
	{"Markus tried to stronghold the foe", "To prevent it from moving",
	"The foe is unable to move now!",
	"Yurinka got into the way. Markus apologized three times",
	"The foe turned to be more slippery than prevented",
	"The foe could not be aprehended so easily tho"}
	,
	{"Markus pulled his first aid kit.", "And tried to assist his ally",
	"Markus healed his target successfully",
	"Markus brought vodka instead of sanitary alcohol?",
	"Markus forgot to buy new needles. Better not.",
	"Markus is busy trying to find the antiseptic."}
	,
	{"Ola pulled a zapping stun gun", "And fired bolts at the foe",
	"The enemy was electrocuted with needless intensity",
	"Ola's zapper blew a fuse and only smoke came out of it",
	"Ola decided to shock Yurinka as a prank instead",
	"Ola mishandled the zapper and got a mild shock herself"}
	,
	{"Ola pulled a mechanical punch", "that stretched a long distance",
	"The enemy received a devastating blow!",
	"The punch was missing a screw and dismantled mid-air",
	"The trajectory was too predictable and the enemy dodged it",
	"The punch was mere centimeters short from the target"}
	,
	{"Ola pulled a tiny drill", "that started spinning at high RPM",
	"The drill pierced through the foe's armor",
	"The drill got stuck. It clearly needs to be greased",
	"Ola used the wrong tip size. Nothing was pierced",
	"The drill's tip was sent flying and missed the target"
	}
	,
	{"The enemy drone fired a round of tiny bullets", "against its target",
	"The diminutive bullets impacted, wreaking havoc.",
	"The drone missed its target completely",
	"The drone miscalculated the foe's moving speed",
	"The drone needs to reload its ammo"}
	,
	{"The enemy scanned a target", "Searching for its vitals",
	"The target's defense has been compromised",
	"A seagull passed in front of the target",
	"The target has mild fever and thus the scan failed",
	"The scanner's software glitched and rebooted"}
	,
	{"The enemy deployed a magnetic field", "And its ally was protected",
	 "The enemy increased it's resistance",
	 "The magnetic field was too weak to do anything",
	 "Interferences made the field vanish",
	 "The magnetic field has so many holes it's of no use"}	
	};
