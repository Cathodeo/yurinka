#include <room.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* get_room_txt_file(int current_room) {
    char file_string[15];
    char *formatted;
    snprintf(file_string, 15, "ROOM/RO%d.txt", current_room);
    formatted = (char *)malloc(15 * sizeof(char));
    strcpy(formatted, file_string);
    return formatted;
}		

Room getRoomObjects(int room_id) {
    Room room;
    room.room_id = room_id;	
    
    // Initialize all objects to a default state
    for (int i = 0; i < 3; i++) {
        room.objects[i] = (Object){0, 0, 0, 0, 0}; 
    }

    switch (room_id) {
        case 1:
            room.objects[0] = (Object){230, 150, 210, 30, 1}; 
            room.objects[1] = (Object){249, 259, 160, 39, 2}; 
            room.objects[2] = (Object){452, 82, 60, 35, 3};  
            break;
        case 2: 
            room.objects[0] = (Object){459, 100, 50, 130, 1}; 
            room.objects[1] = (Object){230, 120, 30, 65, 2}; 
            room.objects[2] = (Object){294, 140, 25, 40, 3};  
            break;
        case 3: 
            room.objects[0] = (Object){190, 17, 300, 180, 1}; 
            room.objects[1] = (Object){120, 123, 30, 65, 2}; 
            room.objects[2] = (Object){0, 0, 0, 0, 0};  
            break;
        case 4:
			room.objects[0] = (Object){266, 95, 90, 150, 1}; 
            room.objects[1] = (Object){64, 281, 500, 30, 2}; 
            room.objects[2] = (Object){173, 246, 70, 40, 3};  
            break;
        case 5:
			room.objects[0] = (Object){145, 36, 350, 65, 1}; 
            room.objects[1] = (Object){145, 111, 350, 98, 2}; 
            room.objects[2] = (Object){145, 212, 350, 90, 3};  
            break;
			
        default:
           
            break;
    }
    
    return room; 
}


int isMouseHovering(int mouse_x, int mouse_y, Object obj) {	
    if (mouse_x >= obj.x && mouse_x <= (obj.x + obj.width) &&
        mouse_y >= obj.y && mouse_y <= (obj.y + obj.height)) {
        return 1;  // Mouse is hovering over the object
    }
    return 0;  // Mouse is not hovering
}  // Missing brace was added here

void hoverText(int room_id, int object_id) {
    switch (room_id) {
        case 1:
            switch (object_id) {
                case 1:
                    triple_dialog("The control room monitors", 
                                  "I spend every weekend evening",
                                  "Watching garbage in this room");
                    rest(20);
                    break;
                case 2:
                    triple_dialog("Makes sense to head to the exit",
                                  "There is no food in this room",
                                  "I ran out of cans of turistic meat");
                    rest(20);
                    break;
                case 3:
                    triple_dialog("It's already 5 in the evening",
                                  "I recall today we had something to do",
                                  "For the first time in ages");
                    break;
            }
            break;	
        case 2:
             switch (object_id) {
                case 1:
                    triple_dialog("The control room door", 
                                  "Also known as where I spend most of my time",
                                  "Plotting world dominance (Or something)");
                    rest(20);
                    break;
                 case 2:
                    triple_dialog("Upstairs", 
                                  "For what is supposed to be a secret base",
                                  "it would take a couple of hours of research to find us.");
                    rest(20);
                    break;
                  case 3:
                    triple_dialog("I don't even remember what was down that alley", 
                                  "I have been here for months and basically only",
                                  "commute from the parking to the monitors. ");
                    rest(20);
                    break; 
                   
          }
          break; 
        case 3:
           switch (object_id) {
                case 1:
                    triple_dialog("The moon is shining above Baltycmorsk", 
                                  "The seaside breeze mixes with the stench of",
                                  "gasoline and rusty metal.");
                    rest(20);
                    break;
                 case 2:
                    triple_dialog("This is the backdoor of our base", 
                                  "We have contacts on the national security department",
                                  "so in theory no one is going to bother us here.");
                    rest(20);
                    break;
                  case 3:
                    break;
        }
        break;     
        
        case 4:
			switch(object_id) {
			case 1:
				    triple_dialog("The only fridge that I see here", 
                                  "It does not look like anyone is maintaining",
                                  "this room. I did not even remember this was here");
                    rest(20);
                    break;
			case 2:
					triple_dialog("Do I want to go back to the corridor already?", 
                                  "",
                                  "");
					rest(20);
					break;
			case 3:
					triple_dialog("One thing is that the children on this organization", 
                                  "spend their days lazing around as I do, but they",
                                  "could clean a little from time to time!");
					rest(20);
					break;
		
			}
			break;
			
		    case 5:
				switch(object_id) {
				case 1:
						triple_dialog("Aborrhent marinated pickles, ", 
									  "repugnant jam. Disgusting moldy bread,",
									  "decomposing fruit, calamity in a jar...");
						rest(20);
						break;
				case 2:
						triple_dialog("Archane potatoes, an ex-orange, ", 
									  "leaking abominations, a loaf of anthrax,",
									  "undead mermelade... and is that a dead mouse?");
						rest(20);
						break;
				case 3:
						triple_dialog("A huge can of putrid herring in vinegar", 
									  "a coffin for the turistic meat of yesteryear,",
									  "pierogi in questionable condition...");
						rest(20);
						break;
			
				}
			break;	
           
    }
}  // Missing brace was added here

int execute_pnc_action(int room_id, int object_id, int switches)
{
    int done = 0;
    while (!done)
    {
        // Update buffer and display based on room_id and object_id
        switch (room_id) {
            case 1:
                switch (object_id) {
                    case 1:
                        triple_dialog("This whole ministry of happiness...",
                                      "The regime used to be more subtle",
                                      "They are starting to panic and hence acting desperate");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(50);
                        
                        
						
                        triple_dialog("Why do we spend our days gossiping propaganda",
                                      "and bitching about the government while we do nothing",
                                      "useful to overthrow it...");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        while (!key[KEY_ENTER]) {
                            rest(20);
                        }
						 rest(50);

                        triple_dialog("It must be that our organization is",
                                      "the only thing even more derailed than the",
                                      "stupid regime we are in. Whatever");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        while (!key[KEY_ENTER]) {
                            rest(20);
                        }
						rest(50);
                        done = 1;  // Exit loop after the last dialog
                        break;

                    case 2:
						stop_ambiance();
                        triple_dialog("To the corridor we go!",
                                      "Actually only I",
                                      "Who am I talking to anyways?");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        while (!key[KEY_ENTER]) {
                            rest(20);
                        }
               
                        done = 1;
                        return 2;
                        break;

                    case 3:
                        // Handle case 3 (if needed)
                        done = 1;
                        break;
                }
                break;
            case 2:
				switch (object_id) {
					 case 1:
						if (switches == 0) {
                        triple_dialog("I don't want to keep watching propaganda",
                                      "and pirated radio on the control room",
                                      "can I focus for a moment and find the kitchen?");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(20);}
                       
                        if (switches == 1) {
						triple_dialog("I finally get to sit and eat,",
						"Laze around and repeat. Although...",
						"I have the feeling I forgot something...!");
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
							while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(50);
                        return 7;
						}
                        done = 1;
                     
                        break;
                        
                        case 2:
                        triple_dialog("Let's go to take some fresh air,",
						"I barely see the daylight for half a year.",
						"I wish I lived on the southern countries or something");
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						     while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(50);
                        done = 1;
                        return 3;
                        break;
                        
                        case 3:
                        if (switches == 0) {
                        triple_dialog("To the depths of darkness we go",
                        "I have a feeling something bad is coming today",
                        "But whatever perils come to me, better if i am full");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(50);
                        done = 1;
                        return 4;
                        break;}
                        
                        if (switches == 1) {
						triple_dialog("Now I remember. That's where the",
                        "rancid smelled room with the fridge is.",
                        "I think I should head back to the control room");
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
                        }
                        rest(50);
                        done = 1;
                        break;
						}
					}
					
					case 3:
					switch(object_id) {
						case 2:
							triple_dialog("Maybe I should get back to the base",
							"",
							"");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							done = 1;
							return 2;
							break;
						default:
						break;
						
					}
					
				break;
				
				case 4:
					switch(object_id) {
						case 1:
							if (switches == 0) {
							triple_dialog("The stench of rotting vegetables can be felt",
							"a kilometer away. Is the fridge even connected to begin with?",
							"Yikes. I hesitate to even dare to open this");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							triple_dialog("Opening the fridge?",
							"",
							""); 
							choice_picker_text("(1) Yeah!", "(2) Yikes!", "", 3);
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
							
							while (!key[KEY_1] && !key[KEY_2])  {
                            // Wait for choice
                            rest(20);
							}
						
							choice_picker_base(buffer, 3);
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
							if (key[KEY_1])
							{
							triple_dialog("We don't hesitate!",
							"Let's see what we can find inside...",
							"");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							done = 1;
							return 5;}
							
							if (key[KEY_2])
							{done = 1;
						    rest(20);
							break;}
							}
							
							if (switches == 1)
							{
							triple_dialog("I don't think I want to take anything else",
							"from that stinky fridge. I should report to the org logistics",
							"that it needs to be sprayed with Domestikos");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							break;
							}
							break;
							
						case 2:
							return 2;
						break;
						
						case 3:
						break;
					}
					break;
					
					case 5:
					 switch(object_id){
						case 1:
						triple_dialog("Thinking about it, the pickles might not",
							"give me too much diarrhea. Plus they are low in calories",
							"and my sedentary lifestyle does not need many anyways");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							return 4;
							break;
						
						
						case 2:
						triple_dialog("Thinking about it, there seems to be a",
							"little jar of jam that looks edible. I can eat it",
							"with a coffee spoon or something, in lieu of bread...");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							return 4;
							break;
						
					
						case 3:
						triple_dialog("The turistic meat has expiry date for the next",
							"year. I am wondering why it's preserved on a fridge tho.",
							"This one claims to be made with 40% of actual meat!");
							blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						    while (!key[KEY_ENTER]) {
                            // Wait for Enter key press
                            rest(20);
							}
							rest(50);
							return 4;
							break;
					}
					break;
		}
        // Small delay between frames
        rest(50);
        return room_id;
   }
 }







int check_hover(Room room, int mouse_x, int mouse_y, int switches) 
{
	int room_from_pnc = room.room_id; 
    for (int i = 0; i < 3; i++) {
    printf("DEBUG: Checking object %d in room %d\n", i, room.room_id);
    printf("DEBUG: Mouse (x=%d, y=%d), Object (x=%d, y=%d, width=%d, height=%d)\n",
           mouse_x, mouse_y, room.objects[i].x, room.objects[i].y, 
           room.objects[i].width, room.objects[i].height);
    
    if (isMouseHovering(mouse_x, mouse_y, room.objects[i])) {
        printf("DEBUG: Hover condition met for object %d in room %d!\n", 
        room.objects[i].object_id, room.room_id);
        hoverText(room.room_id, room.objects[i].object_id);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b & 1) {
		room_from_pnc = execute_pnc_action(room.room_id, room.objects[i].object_id, switches);
		}
        return room_from_pnc; 
    }
    triple_dialog("", "", "");
}
   return room_from_pnc;
}






