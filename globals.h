//=================================================================
// The header file for general settings for the project
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#ifndef GLOBAL_H
#define GLOBAL_H
#include "mbed.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
// #include "SDFileSystem.h"
#include "MMA8452.h"
#include "Nav_Switch.h"


// === [global object] ===
extern uLCD_4DGL uLCD;      // LCD Screen
extern Serial pc;           // USB Console output
// extern SDFileSystem sd;
extern DigitalIn button1;   // Pushbuttons
extern DigitalIn button2;   // ...
extern DigitalIn button3;   // ...
extern Nav_Switch navs;     // Nav Switch
extern AnalogIn jx;         // Joystick
extern AnalogIn jy;         // ...
extern DigitalIn jz;        // ...
extern AnalogOut DACout;    // Speaker
extern PwmOut speaker;      // ...
extern wave_player waver;   // Wave player
extern DigitalOut MBEDLED1;
extern DigitalOut MBEDLED2;
extern DigitalOut MBEDLED3;
extern DigitalOut MBEDLED4;

// === [global settings] ===
extern int DIST_MISSILE_EXPLOSION;

#define F_DEBUG   1                     // Debug flag

#define PI 3.1415926

#define BACKGROUND_COLOR 0x000000 //black
#define YELLOW 0xFFE0 //yellow
#define RED 0xF800 //red
#define ORANGE 0xFD20 //orange
#define WHITE 0xFFFF //white

#define PLAYER_MISSILE_LENGTH 18

#define STATUS_BAR_HEIGHT 7         // Height of status bar
#define LANDSCAPE_HEIGHT 4          // Pixel count for landscape at bottom of screen for the city
#define MAX_BUILDING_HEIGHT 10      // Pixel count for height of city buildings
#define CITY_HIT_MARGIN 1           // Pixel count for hit margin around building in city
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

#define NO_RESULT 0
#define ACTED 1
#define GAME_OVER -1
#define NO_ACTION 0
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_C 3
#define BUTTON_X 4
#define GO_LEFT 5
#define GO_RIGHT 6
#define GO_UP 7
#define GO_DOWN 8

#define LEVEL_ADVANCE 9
#define MISSILE_HIT_POINTS 10


#define PLAYER_HIT 1
#define NO_CITY_HIT -1


// === [define the macro of error handle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        uLCD.printf("\nERROR:%d\n",e); \
        pc.printf("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood
// Missle error codes ...
#define ERROR_MISSILE_INDEX_GET_INFO      -1  //< make sure your code gives the valid index for missile_get_info()
#define ERROR_MISSILE_INDEX_UPDATE_STATUS -2  //< make sure your code gives the valid index for missile_update_status()
#define ERROR_MISSILE_SPEED               -3  //< missile speed has to be between 1 and 8
#define ERROR_MISSILE_INTERVAL            -4  //< missile interval has to be between 1 and 100
#define ERROR_CITY_NUMBER                 -11 //< num_city in city_landscape_init() is larger than MAX_NUM_CITY
#define ERROR_CITY_INDEX_GET_INFO         -12 //< make sure your code gives the valid index for city_get_info()
#define ERROR_CITY_INDEX_DEMOLISH         -13 //< make sure your code gives the valid index for city_demolish()
// DLL error codes ...
#define ERROR_DLL_INSERT_HEAD             -14 //< inserting into doubly linked list at head failed
#define ERROR_DLL_DELETE                  -15 //< deleting node from doubly linked list failed

#endif //GLOBAL_H
