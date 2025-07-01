//=================================================================
// The header file defining the missile module
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//missile
//==================================================================
#ifndef MISSILE_PRIVATE_H
#define MISSILE_PRIVATE_H

#include "mbed.h"
#include "globals.h"
#include "missile_public.h"

//==== [private settings] ====
#define  MISSILE_INTERVAL  10
#define  MISSILE_SPEED  6
#define MISSILE_COLOR    0xFF0000

//==== [private type] ====

//==== [private function] ====
void missile_create(void);
void missile_update_position(void);
void missile_draw(MISSILE* missile, int color);

#endif //MISSILE_PRIVATE_H


