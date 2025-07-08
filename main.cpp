//=================================================================
// The main program file.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>
#include <math.h>

// Project includes
#include "doubly_linked_list.h"
#include "globals.h"
#include "hardware.h"
#include "city_landscape_public.h"
#include "missile_private.h"
#include "missile_public.h"
#include "player_public.h"


/////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL VARS

int DIST_MISSILE_EXPLOSION = 10;


/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION PROTOTYPES
int setup_libs();
void status_bar(PLAYER player);
void set_random_seed(Timer);
int get_action(GameInputs in);
int perform_action(int action);
int update_game(PLAYER player);


int missile_distance(int x1, int y1, int x2, int y2); // calculate euclidean distance
void missile_contact(void); // iterate through missiles and see if any collided
int was_player_hit(void);
int update_city_landscape(void);
int who_got_hit(int missile_x);
void playSound(char * wav);
void playNotes(void);
void advance_level(void);

/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION DEFINITIONS
/**
 * MAIN
 * 
 * Program entry point! This is where it all begins.
 * This function is for all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{

    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    pc.printf("Program Starting\r\n");

    int status = setup_libs();

    if (status == ERROR_DLL_INSERT_HEAD || 
        status == ERROR_DLL_DELETE) {
            exit(1);
    }

    // Init game states and variables
    pc.printf("Init game states \r\n");

    // Timer to measure game update speed
    // (secondarily used to generate random seed)
    Timer t;
    set_random_seed(t);

    // Game variables
    int num_city = 4;       // Number of cities
    // Game init functions
    //// Init city landscape with specified num of city
    city_landscape_init(num_city);
    //// Init the missile structure
    missile_init();
    //// Init the player structure
    player_init(num_city);

    pc.printf("Initialization complete\r\n");
    
    // Main Game Loop
    while(1)
    {
        // Start time to measure game update speed
        t.start();

        /** 1. Read inputs 
         * TODO: implement read_inputs() function in hardware.cpp
         */
        GameInputs inputs = read_inputs();

        /** 2. Determine action (move, action, menu, etc.)
         * TODO: implement get_action() function:
         */
        int action = get_action(inputs);

        /** 3. Determine action (move, action, menu, etc.)
         * TODO: implement perform_action() function:
         */
        int state = perform_action(action);

        /** 4. Update game
         * TODO: implement update_game() function:
         */
        PLAYER player = player_get_info();
        int result = update_game(player);
        
        status_bar(player);

        /** 5. Check game state 
         * Check for game Over or similar and handle
         */
        if (result == GAME_OVER) {
            pc.printf("GAME OVER \r\n");
            uLCD.printf("\n GAME OVER \n");
            break;
        }

        // Compute update time
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }

    // Tear down
    pc.printf("Tearing down ...\r\n");
    
    destroyList(get_missile_list());
    destroyList(player_get_info().playerMissiles);

    pc.printf("Complete ... Exiting! \r\n");
    return 0;
}

/**
 * SET_RANDOM_SEED
 * 
 * This function randomly sets a seed.
 * @param t: Timer object
 * @return void
 */
void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();
    uLCD.printf("Push any button to start.\n");
    while(1){
      inputs = read_inputs();
      if (inputs.b1 || inputs.b2 || inputs.b3) break;
      }
    uLCD.cls();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
}

/**
 * SETUP_LIBS
 * 
 * This function handles the custom/imported library setups
 * Tests the imported DLL.
 * @return int: The action that matches the read inputs
 */
int setup_libs()
{
    // Test DDL
    pc.printf("Testing DDL\r\n");

    testDLL();
    
    pc.printf("[OK]...\r\n");
    return ERROR_NONE;
}

/**
 * STATUS_BAR
 *
 * This updates the status bar at the top.
 * @param player: The player object
 * @return void
 */
void status_bar(PLAYER player) {
    uLCD.filled_rectangle(0, 0, 160, STATUS_BAR_HEIGHT, BLACK);
    char str[1024];
    snprintf(str,sizeof(str),"TA|P:%d,%d S:%d \n HEALTH: %d \n", 
        player.x, player.y, player.score, player.status);
    uLCD.text_string(str,0,0,FONT_7X8,RED);
}

/**
 * GET_ACTION
 *
 * TODO:
 * This function gets the desired acrtion based in read inputs
 * This function gets the appropriate action based on read inputs.
 * @param in: The read game inputs structure
 * @return int: The action that matches the read inputs
 */
int get_action(GameInputs in) {
#ifdef F_DEBUG
    pc.printf("[F] get_action()\r\n");
#endif 
  // 1. Check your button inputs and return the corresponding action value
  if (player_get_info().score != 0 && player_get_info().score%100 == 0 || (in.b1 && in.b2)) {
        DIST_MISSILE_EXPLOSION-=2;
      return LEVEL_ADVANCE;
  }
  if (in.b2 || in.ns_up) {
      return GO_RIGHT;
  } else if (in.b1 || in.ns_left) {
      return GO_LEFT;
  }
  if (in.b3 || in.ns_down) {
      return BUTTON_X;
      pc.printf("button 3 pressed !!!!!!");
  }

  // 2. Check your navigation switch and return the corresponding direction value
  //return new changes

  // 3. If no button is pressed, just return no action value
  return NO_ACTION;
}

/**
 * PERFORM_ACTION
 *
 * TODO: 
 * This function performs the appropriate action based on read inputs.
 * @param action: A desired action
 * @return int: Outcome of the performed action
 */
int perform_action(int action) {
#ifdef F_DEBUG
    pc.printf("[F] perform_action()\r\n");
#endif
    // 1. Perform the appropriate movement or action. E.g.: if the desired action is
    //    to move the player left, then move the player left. For this, you might find 
    //    implementing and using the player_move_left() a dn similar helper function 
    //    very useful. 
    // 2. If an action is taken, return accordingly. Might find ACTED and NO_RESULT useful.
    // 3. Feel free to extend the switch() to perform action for other buttons.

    switch(action)
    {
        case GO_LEFT:
            /**
             * TODO: Moves the player left. You might find it helpful to find player_moveLeft().
             */
            player_moveLeft();
            return ACTED;

        case GO_RIGHT:
            /**
             * TODO: Moves the player right. You might find it helpful to find player_moveRight().
             */
            player_moveRight();
            return ACTED;


        case BUTTON_X:
            /**
             * TODO: Performs a fire action. You might find it helpful to find player_fire().
             */
             player_fire();
            return ACTED;

        case LEVEL_ADVANCE:

            advance_level();
            return ACTED;

    }

    return NO_RESULT;
}
/**
 * UPDATE_GAME
 *
 * TODO:
 * This function updates the game based on the user action. For example, if
 * the user requests GO_LEFT, then the function should check if that is
 * possible (not on left edge) and move player accordingly.
 * @param player A (deep) copy of the player instance
 * @return a result value based on game state
 */
int update_game(PLAYER player) {
#ifdef F_DEBUG
    pc.printf("[F] update_game()\r\n");
#endif


    
    // 1. Generate and draw the enemy missiles.
    missile_generator();
    //  HINT: Look at the Missile class
    
    // 2. Draw the playyer's missile, as needed.
    //  HINT: Look at the Player class
    player_missile_draw();
    // 3. Update the city landscape. If an enemy missile hits a the city,
    //      you want to update the count and other related things.
    //      HINT: It would be useful to implement update_city_landscape()
    
    // 4. Check if the player is hit by an enemy missile.
    //      HINT: It would be useful to implement was_player_hit()
    was_player_hit();
    if (player.status == DESTROYED || update_city_landscape() == 0) {
        return GAME_OVER;
    }

    // 5. Compute player missile colliding/destroying enemy missile on contact.
    //      HINT: It would be useful to implement missile_contact()
    missile_contact();
    // 6. Check for game status from city remaining, player hit. Return GAME_OVER
    //      if no cities are remaining or if player is hit.


    return NO_RESULT;
}

/**
* 
* Update the information for the game
*/
void advance_level(void) {
    MISSILE_SPEED += 3;
    MISSILE_INTERVAL -= 3;

}
/**
 * MISSLE_DISTANCE
 *
 * TODO:
 * This function gets the euclidean distance between two points.
 * @param x1 The x-coordinate of point 1
 * @param y1 The y-coordinate of point 1
 * @param x2 The x-coordinate of point 2
 * @param y2 The y-coordinate of point 2
 * @return a result value based on game state
 */
int missile_distance(int x1, int y1, int x2, int y2) {
#ifdef F_DEBUG
    pc.printf("[F] missile_distance()\r\n");
#endif
    // 1. Compute and return the euclidean distance between two 
    //      points (x1,y1) and (x2,y2).
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x_squared = dx * dx;
    int y_squared = dy * dy;
    return (int) (sqrt((double)(x_squared + y_squared)));
}

/**
 * MISSLE_CONTACT
 *
 * TODO:
 * This function checks if the player's missile collides with the enemy
 * missiles.
 * @return void
 */
void missile_contact(void) {
#ifdef F_DEBUG
    pc.printf("[F] missile_contact()\r\n");
#endif
    // 1. Get the player's missiles, enemy missiles
    //      HINT: Might be useful to take a look at player_get_info() and get_missile_list().
    // 2. Check for contact between a player missile and an enemy missile
    //      2a. Loop through player's missiles list
    //      2b. For each player missile, loop through enemy missiles list
    //      2c. Check for contact by deducing the distance between both missiles
    //      2d. If the distance is below the threshold of DIST_MISSILE_EXPLOSION,
    //          2d1. Both the player missile and enemy will explode, so update their status
    //                  This might impact the score for the player.

    DLinkedList* playerMissiles = player_get_info().playerMissiles;
    DLinkedList* enemyMissiles = get_missile_list();
    LLNode* currPlayMissile  = playerMissiles->head;
    //LLNode* currEnMissile  = enemyMissiles->head;
    while (currPlayMissile != NULL) {
        MISSILE* currPlayer = (MISSILE*) currPlayMissile->data;
        if (currPlayer->status == MISSILE_ACTIVE) {
            LLNode* currEnMissile = enemyMissiles->head; 

            while (currEnMissile != NULL) {
                MISSILE* currEnemy = (MISSILE*)(currEnMissile->data);
                if (missile_distance(currPlayer->x, currPlayer->y, currEnemy->x, currEnemy->y) <= DIST_MISSILE_EXPLOSION) {
                    currEnemy->status = MISSILE_EXPLODED;
                    currPlayer->status = MISSILE_EXPLODED;
                    missile_explode(currPlayer->x, currPlayer->y);
                    player_update_score(MISSILE_HIT_POINTS);
                }
                currEnMissile = currEnMissile->next;
            }
            currPlayMissile = currPlayMissile->next;
        }
    }



}

/**
 * UPDATE_CITY_LANDSCAPE
 *
 * TODO:
 * This function updates the city landscape.
 * @return int: number of remaining cities
 */
int update_city_landscape(void){
#ifdef F_DEBUG
    pc.printf("[F] update_city_landscape()\r\n");
#endif
    // 1. Get enemy missiles.
    // 2. Looping through all enemy missiles
    //     2a. Deduce if and what city got hit.
    //             HINT: Might be helpful to take a look at who_got_hit()
    //     2b. If the missile hits a city, the missile explodes. You might to update the city information 
    //             for the player, using player_update_city()
    //     2c. If the missile hits the ground and not city, the missile explodes
    // 3. Return the number of city left.

    DLinkedList* missiles = get_missile_list();
    LLNode* curr  = missiles->head;
    LLNode* nextNode = NULL;
    while (curr != NULL) {
        MISSILE* currMissile= (MISSILE*) curr->data;
        nextNode = curr->next;
        if (currMissile->status == MISSILE_ACTIVE) {
            if (currMissile->y >= CITY_UPPER_BOUND) {
                 int hit_city_index = who_got_hit(currMissile->x);
                if (hit_city_index != -1) {
                    city_demolish(hit_city_index);
                    player_update_city();
                    currMissile->status = MISSILE_EXPLODED;
                    missile_explode(currMissile->x, currMissile->y);

                } else if (currMissile->y >= (SIZE_Y - LANDSCAPE_HEIGHT)) { 
                    currMissile->status = MISSILE_EXPLODED; 
                    missile_explode(currMissile->x, currMissile->y);

                }
            }
        }
        curr = nextNode;
    }
    int cities_remaining = 0;

    for (int i = 0; i < MAX_NUM_CITY; i++) {
        if (city_record[i].status == EXIST) {
            cities_remaining++;
        }
    }
    
    
    // Return the actual count of cities remaining
    return cities_remaining; // FIX: Return the calculated count
}

/**
 * WAS_PLAYER_HIT
 *
 * TODO:
 * This function checks if the player was hit by enemy missile. HINT: If player is hit,
 * you might want to return PLAYER_HIT.
 * @return int: number of remaining cities
 */
int was_player_hit() {
#ifdef F_DEBUG
    pc.printf("[F] was_player_hit()\r\n");
#endif
    // 1. Get enemy missiles.
    // 2. Looping through all enemy missiles
    //      2a. Check if an enemy missile hits a player
    //      2b. If missile hits player, the player is destroyed. Check player_destroy()
    //      2c. The missile also explodes, so update accordingly.
    // 3. Return the status of the player being hit by a missile. Check PLAYER_HIT.
    DLinkedList* enemyMissiles = get_missile_list();
    LLNode* curr  = enemyMissiles->head;
    LLNode* nextNode = NULL;
    while (curr != NULL) {
        MISSILE* currMissile= (MISSILE*) curr->data;
        nextNode = curr->next;
        if (currMissile->status == MISSILE_ACTIVE) { 
            
            if (missile_distance(currMissile->x, currMissile->y, player_get_info().x, player_get_info().y) <= DIST_MISSILE_EXPLOSION) {
                    player_destroy();
                    currMissile->status = MISSILE_EXPLODED; 
                    missile_explode(currMissile->x, currMissile->y);
                    return PLAYER_HIT;
            }
        }
    curr = nextNode;
    }
    return NO_RESULT;
}

/**
 * WHO_GOT_HIT
 *
 * TODO:
 * This function checks and gets which city got hit.
 * @param missile_x: the x-coordinate of a missile
 * @return int: index of the city that was hit. If no city is hit, returns -1.
 */
int who_got_hit(int missile_x) {
#ifdef F_DEBUG
    pc.printf("[F] who_got_hit()\r\n");
#endif
    // 1. Loop through all cities.
    // 2. If the city exists,
    //     2a. Check if the exact city at this index was hit. NOTE: We alsoready know a city was hit (y-axis wise)
    //     2b. Return the index of the city if it was hit.
    // 3. If none is found, return -1.
    for (int i = 0; i< MAX_NUM_CITY; i++) {
        CITY current_city = city_record[i]; 
        if (current_city.status == EXIST) {
            if (missile_x >= current_city.x && missile_x < (current_city.x + current_city.width)) {
                return i;
            }

        }
    }
    return -1;

}

/**
 * PLAYSOUND
 *
 * This function plays a wav sound file.
 * @param fn_wav: filename of the wav file.
 * @return void
 */
void playSound(char* fn_wav)
{
#ifdef F_DEBUG
    pc.printf("[F] playSound()\r\n");
#endif
    //open wav file
    FILE *wave_file;
    wave_file=fopen(fn_wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", fn_wav);
        return;
}

/* Wanna hear some annoying sounds?*/
/**
 * PLAYNOTES
 *
 * This function plays a note (Wanna hear some annoying sounds? :) ).
 * @return void
 */
void playNotes(void)
{
#ifdef F_DEBUG
    pc.printf("[F] playNotes()\r\n");
#endif
    int i;
    // generate a 500Hz tone using PWM hardware output
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(3);
    speaker=0.0; // turn off audio
    wait(2);
    // generate a short 150Hz tone using PWM hardware output
    // something like this can be used for a button click effect for feedback
    for (i=0; i<10; i++) {
        speaker.period(1.0/150.0); // 500hz period
        speaker =0.25; //25% duty cycle - mid range volume
        wait(.02);
        speaker=0.0; // turn off audio
        wait(0.5);
    }

    // sweep up in frequency by changing the PWM period
    for (i=0; i<8000; i=i+100) {
        speaker.period(1.0/float(i));
        speaker=0.25;
        wait(.1);
    }
    wait(2);

    // two tone police siren effect -  two periods or two frequencies
    // increase volume - by changing the PWM duty cycle
    for (i=0; i<26; i=i+2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    // decrease volume
    for (i=25; i>=0; i=i-2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    speaker =0.0;
    wait(2);
}
