//=================================================================
// Implementation for the player module
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#include "doubly_linked_list.h"
#include "missile_private.h"
#include "missile_public.h"
#include "player_private.h"
#include "player_public.h"

PLAYER player; // structure of player

PLAYER player_get_info(
    void) { // getter for user to acquire info without accessing structure
#ifdef F_DEBUG
  pc.printf("[F] player_get_info()\r\n");
#endif
  return player;
}

void player_set_info(PLAYER p) {
    player = p;
}

/**
 * Initialize the player's position, missile status, draw player
 * @param num_city The missile to be drawn
 */
void player_init(int num_city) {
#ifdef F_DEBUG
  pc.printf("[F] player_init()\r\n");
#endif
  player.x = PLAYER_INIT_X;
  player.y = PLAYER_INIT_Y;
  player.status = THREE_HEARTS;
  player.playerMissiles = create_dlinkedlist();
  player.delta = PLAYER_DELTA;
  player.width = PLAYER_WIDTH;
  player.height = PLAYER_HEIGHT; //Should i change this to 11 with sprite change?
  player.score = 0;
  player.num_city = num_city;
  player.super_missiles_left = 3;  // give 3 super shots
  player_draw(PLAYER_COLOR);
}

/**
 * Move player PLAYER_DELTA pixels to the left.
 */
void player_moveLeft(void) {
#ifdef F_DEBUG
  pc.printf("[F] player_moveLeft()\r\n");
#endif
  // 1. Erase player on current position
  // 2. Deduce new valid position
  // 3. Draw player on new position

  if (player.x - player.delta >= 0) {
    player_draw(BACKGROUND_COLOR);
    player.x -= player.delta;
    player_draw(PLAYER_COLOR);
  }
}

/**
 * TODO:
 * Move player PLAYER_DELTA pixels to the right.
 */
void player_moveRight(void) {
#ifdef F_DEBUG
  pc.printf("[F] player_moveRight()\r\n");
#endif
  // 1. Erase player on current position
  //    HINT: You want to make sure you can move to the new
  //        position effected by 'player.delta'
  // 2. Deduce new valid position
  // 3. Draw player on new position
    if (player.x + player.width + player.delta <= 128) {
    player_draw(BACKGROUND_COLOR);
    player.x += player.delta;
    player_draw(PLAYER_COLOR);
    }
}

/**
 * TODO:
 * Generate an active missile to shoot.
 */
void player_fire() {
#ifdef F_DEBUG
  pc.printf("[F] player_fire()\r\n");
#endif

  // 1. Initialize a missile from the player's current position
   MISSILE* tempMissile = (MISSILE *)malloc(sizeof(MISSILE));
    tempMissile->source_x = player.x + player.width/2;
    
    tempMissile->x = tempMissile->source_x;
    tempMissile->y = player.y;
    tempMissile->target_x = tempMissile->source_x;
  // 2. Set the status of the missile from player
    tempMissile->status = MISSILE_ACTIVE;
    tempMissile->tick = 0;
  // 3. Add new missile to appropriate DLL object
  insertHead(player.playerMissiles, tempMissile);
}

void player_fire_super(void) {
    PLAYER p = player_get_info();
    if (p.super_missiles_left > 0 && p.status != DESTROYED) {
        // spawn a missile at the ship’s center
        MISSILE* m = missile_create_at(p.x + p.width/2, p.y);
        m->is_super = true;          // flag it
        p.super_missiles_left--;     // consume one
        player_set_info(p);          // write back
    } else {
        playSound("empty.wav");      // out-of-supers feedback
    }
}

/**
 * TODO:
 * Draw/updates the line of any active missiles, "erase" deactived missiles
 */
void player_missile_draw(void) {
#ifdef F_DEBUG
  pc.printf("[F] player_missile_draw()\r\n");
#endif
    //new
  // 1. Initialize the missile
    
  // 2. Looping through all player missiles
  //      2a. If missile status is MISSLE_EXPLODED
  //          1a1. Erase missile on screen and delete appropriately from DLL
  //      2b. Else,
  //          1b1. Update missile position based on speed
  //          1b2. If missile is going off-screen, erase missile and delete
  //          approrpiately from DLL 1b3. Else, draw missile at new location.
  //  NOTE: You don't have to necessarily show the trace of the missile.
  //        To draw the missile, you can use the uLCD.line(). A similar library
  //              is used in missile.cpp
    LLNode *currNode = player.playerMissiles->head;
    LLNode *nextNode = NULL; //new node
    while (currNode != NULL) {
        MISSILE* currentMissile = (MISSILE*)(currNode->data);
        nextNode = currNode->next;
        uLCD.line(currentMissile->x, currentMissile->y,
                          currentMissile->x, currentMissile->y + PLAYER_MISSILE_LENGTH, BLACK);
        if (currentMissile->status == MISSILE_EXPLODED) {
                free(currentMissile); 
                deleteNode(player.playerMissiles, currNode);
        } else {
            currentMissile->y -= MISSILE_SPEED; 
            if(currentMissile->y + PLAYER_MISSILE_LENGTH < 0) {
                free(currentMissile); 
                deleteNode(player.playerMissiles, currNode);
            } else {
                uLCD.line(currentMissile->x, currentMissile->y,
                          currentMissile->x, currentMissile->y + PLAYER_MISSILE_LENGTH, BLUE);
            }
            
        }
        currNode = nextNode;
    }
  
}

//Example declaration:
const char *healthyShip =   "00000W00000"
                            "00000W00000"
                            "0000WWW0000"
                            "0000WWW0000"
                            "00G0WWW0G00"
                            "00W0WGW0W00"
                            "G0BWGWGWB0G"
                            "W0WWWWWWW0W"
                            "WWWWGWGWWWW"
                            "WW0GG0GG0WW"
                            "W000000000W";

const char *midShip =       "00000W00000"
                            "00000W00000"
                            "0000WWW0000"
                            "0000WWW0000"
                            "00Y0WWW0Y00"
                            "00W0WYW0W00"
                            "Y0BWYWYWB0Y"
                            "W0WWWWWWW0W"
                            "WWWWYWYWWWW"
                            "WW0YY0YY0WW"
                            "W000000000W";

const char *lastShip =      "00000W00000"
                            "00000W00000"
                            "0000WWW0000"
                            "0000WWW0000"
                            "00R0WWW0R00"
                            "00W0WRW0W00"
                            "R0BWRWRWB0R"
                            "W0WWWWWWW0W"
                            "WWWWRWRWWWW"
                            "WW0RR0RR0WW"
                            "W000000000W";

const char *black =         "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000"
                            "00000000000";

//new comments
// ==== player_private.h implementation ====
void player_draw(int color) {
    if (color == BACKGROUND_COLOR) {
        draw_img(player.x, player.y, black);
    } else if (player.status == THREE_HEARTS) {
        draw_img(player.x, player.y, healthyShip);
    } else if (player.status == TWO_HEARTS) {
        draw_img(player.x, player.y, midShip);
    } else { //ONE_HEART
        draw_img(player.x, player.y, lastShip);
    }
}

 void draw_img(int x, int y, const char *img) {
  int colors[11 * 11];
  for (int i = 0; i < 11 * 11; i++) {
    switch (img[i]) {
    case 'R':
      colors[i] = RED;
      break;
    case 'W':
        colors[i] = WHITE;
        break;
    case 'G':
        colors[i] = GREEN;
        break;
    case 'Y':
        colors[i] = YELLOW;
        break;
    case 'B':
      colors[i] = BLUE;
      break;
    case '0':
      colors[i] = BLACK;
      break;
    default:
      colors[i] = BLACK;
    }
  }
  uLCD.BLIT(x, y, 11, 11, colors);
  wait_us(250); // Recovery time! 
}


void player_update_city(void) { player.num_city--; }

void player_update_score(int point) { player.score += point; }

// destroy and "erase" the player off the screen. change status to DESTROYED
void player_destroy() {
  if (player.status > DESTROYED) {
    player.status = (PLAYER_STATUS)(player.status - 1);
  }
  if (player.status == DESTROYED) {
    player_draw(BACKGROUND_COLOR);
  }
}
