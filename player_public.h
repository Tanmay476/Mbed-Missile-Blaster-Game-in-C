//=================================================================
// The header file is for module "player"
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#ifndef PLAYER_PUBLIC_H
#define PLAYER_PUBLIC_H

#include "doubly_linked_list.h"

typedef enum {
    PMISSILE_EXPLODED = 0,
    PMISSILE_ACTIVE = 1
} PLAYER_MISSILE_STATUS; // is missile active or exploded?

typedef struct {
    int x;                   /// The x-coordinate of missile current position
    int y;                   /// The y-coordinate of missile current position
    PLAYER_MISSILE_STATUS status;   /// The missile status, see PLAYER_MISSILE_STATUS
} PLAYER_MISSILE;

typedef enum {
    THREE_HEARTS = 3,
    TWO_HEARTS = 2,
    ONE_HEART = 1,
    DESTROYED = 0
} PLAYER_STATUS; // is player aircraft alive or destroyed?

typedef struct {
    int x; int y;       // x,y-coordinate of player - top left pixel
    int delta;     // delta x,y
    int width; int height;
    int score;
    int num_city;
    PLAYER_STATUS status;
    DLinkedList* playerMissiles;
    int super_missiles_left;  // number of super missiles left
} PLAYER; // structure for player

//comments
PLAYER player_get_info(void);
void player_init(int); // initialize the player's attributes
void player_moveLeft(void); // move delta pixels to the left 
void player_moveRight(void); // move delta pixels to the right
void player_fire(void); // fire missiles

void player_missile_draw(void); // updates the drawing of missiles on screen
void player_draw(int color);

void player_update_city(void);  // updates the number of citys still active
void player_update_score(int);  // updates the score

//void player_missile_exploded(int i);
//void player_missile_exploded(PLAYER_MISSILE *playerMissile); //method overload

void player_destroy(void); // destroy the player to end game

void player_fire_super(void); // fire a super missile

#endif //PLAYER_PUBLIC_H