//=================================================================
// Implementation of missile module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//missile
//==================================================================

#include "missile_private.h"
#include "doubly_linked_list.h"
#include "missile_public.h"

int missile_tick=0;
int MISSILE_INTERVAL = 10; // Initial default value
int MISSILE_SPEED = 6;    // Initial default value

//Create a DLL for missiles
DLinkedList* missileDLL = NULL;

void missile_init(void)
{
    missileDLL = create_dlinkedlist();
};

/**
 * TODO:
 * See the comments in missile_public.h
 */
void missile_generator(void){
#ifdef F_DEBUG
    pc.printf("[F] missile_generator()\r\n");
#endif

    // 1. Update the missile's tick
    missile_tick++;
    // 2. Create a missile on every interval defined by MISSILE_INTERVAL
    // HINT: Only fire the missile at certain ticks
    if (missile_tick%(MISSILE_INTERVAL) == 0) {
        missile_create();
    }
    // 3. Update missle positions. HINT: Take a look at missile_update_position()
    missile_update_position();
}

/**
 * TODO:
 * See the comments in missile_public.h
 */
void missile_create(void){
#ifdef F_DEBUG
    pc.printf("[F] missile_create()\r\n");
#endif

    // 1. Initialize the missile
    MISSILE* newMissile = (MISSILE *)malloc(sizeof(MISSILE));

    // 2. The missile starts at the top of the screen
    newMissile->y = 0;
    
    // 3. Randomly set a missile source_x and target_x
    newMissile->source_x = rand() % SIZE_X; 
    newMissile->x = newMissile->source_x;
    //  HINT: Keep in mind the width of the screen SIZE_X, and 
    //      set the x-coord of the missle
   newMissile->target_x = rand() % SIZE_X;
    // 4. Set the active status of the missile and 
    newMissile->status = MISSILE_ACTIVE;
    // 5. each missile has its own tick
    newMissile->tick = 0;
    // 6. Insert missile into the appropriate container object.
    insertHead(missileDLL, newMissile);
}

/**
 * TODO:
 * This function update the position of all missiles and draw them
 */
void missile_update_position(void){
#ifdef F_DEBUG
    pc.printf("[F] missile_update_position()\r\n");
#endif

    // 1. Init a missile and define how fast the missile will move. 
    //  You might also want to define dx, dy for the missile
    // 2. Loop through all the missiles
    //      2a. If the missile's status is MISSILE_EXPLODED
    //          2a1. Erase missile by drawing a blank missile on current 
    //                  position, and delete the missle
    //      2b. Else, 
    //          2b1. Erase missile by drawing a blank missile on current position
    //          2b2. Update missile position and draw at new position
    //          2b3. Update missile's internal tick

    LLNode *currNode = missileDLL->head;
    LLNode *nextNode = NULL;
    while (currNode != NULL) {
        MISSILE* currentMissile = (MISSILE*)(currNode->data);
        nextNode = currNode->next;
        if (currentMissile->status == MISSILE_EXPLODED) {
            missile_draw(currentMissile, BLACK);
            free(currentMissile);
            deleteNode(missileDLL, currNode);
        } else {
             missile_draw(currentMissile, BLACK);
             currentMissile->y += MISSILE_SPEED;
             currentMissile->x = currentMissile->source_x +
                                (currentMissile->y * (float)(currentMissile->target_x - currentMissile->source_x) / SIZE_Y);
            if (currentMissile->y >= SIZE_Y) {
                free(currentMissile); 
                deleteNode(missileDLL, currNode);
            } else {
                missile_draw(currentMissile, MISSILE_COLOR);
                currentMissile->tick++;
            }

        }
        currNode = nextNode;
    }

}

/**
 * TODO:
 * Set missile speed (default speed is 4)
 */
void set_missile_speed(int speed){
#ifdef F_DEBUG
    pc.printf("[F] set_missile_speed()\r\n");
#endif

    // Error checking - speed has to be bounded on both sides
    ASSERT_P(speed>=1 && speed<=8,ERROR_MISSILE_SPEED);

    // 1. Set the speed of the missile by setting MISSILE_SPEED as defined
    MISSILE_SPEED = speed;
}

/**
 * TODO:
 * Set missile interval (default interval is 10)
 */
void set_missile_interval(int interval){
#ifdef F_DEBUG
    pc.printf("[F] set_missile_speed()\r\n");
#endif

    // Error checking - missile interval has to be bounded on both sides
   // ASSERT_P(interval>=1 && interval<=100,ERROR_MISSILE_INTERVAL);

    // 1. Set the interval of the missile by setting MISSLE_INTERVAL as defined
    MISSILE_INTERVAL = interval;

}

/**
 * TODO:
 * See comments in missile_public.h
 */
DLinkedList* get_missile_list() {
#ifdef F_DEBUG
    pc.printf("[F] get_missile_list()\r\n");
#endif

    // 1. Return the DLL object that holds missiles.
    return missileDLL;
    
}

/**
 * This function draws a missile.
 * @param missile The missile to be drawn
 * @param color The color of the missile
 */
void missile_draw(MISSILE* missile, int color){
#ifdef F_DEBUG
    pc.printf("[F] missile_draw()\r\n");
#endif

    int init_x, init_y, current_x, current_y;

    init_x = missile->source_x;
    init_y = 0;
    current_x = missile->x;
    current_y = missile->y;

    uLCD.line(init_x, init_y, current_x, current_y, color);
}
