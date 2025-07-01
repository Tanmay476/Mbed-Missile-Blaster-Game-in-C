//=================================================================
// The file is for module "city landscape"
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

#include "city_landscape_private.h"

CITY city_record[MAX_NUM_CITY];
int building_height[NUM_BUILDING];


/**
 * TODO:
 * See the comments in city_landscape_public.h
 * @param num_city is the number of city desired
 */
void city_landscape_init(int num_city) {
#ifdef F_DEBUG
  pc.printf("[F] city_landscape_init()\r\n");
#endif 

    // Error checking - index must be within max
    ASSERT_P(num_city<=MAX_NUM_CITY,ERROR_CITY_NUMBER);

    int i;
    int city_distance = (SIZE_X-CITY_TO_SCREEN_MARGIN*2)/num_city;
    
    // 1. Initialize cities for valid cities, with city info, like the position, width, height. 
    // HINT: Don't forget to update the city's status as EXIST/DEMOLISHED
    for(i=0;i<MAX_NUM_CITY;i++){

    }
    
    // 2. Initialize the height of the buildings

    
    // 3. Draw city, landscape on the screen
    
}

/**
 * TODO:
 * Gets the info for specified city
 * @param index of the city to get its information.
 * @return CITY: The city object ot be returned
 */
CITY city_get_info(int index){
#ifdef F_DEBUG
  pc.printf("[F] city_get_info()\r\n");
#endif 

    // Error checking - index must be within max
    ASSERT_P(index<MAX_NUM_CITY,ERROR_CITY_INDEX_GET_INFO);

    // 1. Return the city object at valid index location as specified
}

/**
 * TODO:
 * Demolishes the specified city
 * @param index of the city to be demoolished,
 */
void city_demolish(int index){
#ifdef F_DEBUG
  pc.printf("[F] city_demolish()\r\n");
#endif 

    // Error checking - index must be within max
    ASSERT_P(index<MAX_NUM_CITY,ERROR_CITY_INDEX_DEMOLISH);

    // 1. Remove the city 
    // 2. Update the status of all that has happened
    // 3. Erase the city. Note, you might also adjust demolishing 
    //          partially (some buildings) on single impact
    // Don't forget to check that specified index is within range.
    
}

/**
 * TODO:
 * Draws the cities
 */
void draw_cities(void){
#ifdef F_DEBUG
  pc.printf("[F] draw_cities()\r\n");
#endif 

    // 1. Loop and draw all possible cities
    //      1a. Within each city, draw all buildings as described

    
}

/**
 * Draws the landscape of the cities.
 */
void draw_landscape(void){
#ifdef F_DEBUG
  pc.printf("[F] draw_landscape()\r\n");
#endif 
    uLCD.filled_rectangle(0, SIZE_Y-1, SIZE_X-1, REVERSE_Y(LANDSCAPE_HEIGHT), LANDSCAPE_COLOR);
}