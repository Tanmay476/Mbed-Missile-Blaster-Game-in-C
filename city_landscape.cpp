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
      if (i<num_city){
        city_record[i].x = CITY_TO_SCREEN_MARGIN + i*city_distance + (city_distance-CITY_WIDTH)/2;
        city_record[i].y = LANDSCAPE_HEIGHT;
        city_record[i].width = CITY_WIDTH;
        city_record[i].height = CITY_HEIGHT;
        city_record[i].status = EXIST;
        building_height[i] = city_record[i].height;
      } else {
        city_record[i].status = DEMOLISHED;
        building_height[i] = 0; // No buildings in demolished cities
    }
  }
    
    // 2. Initialize the height of the buildings
    for(i=0;i<NUM_BUILDING;i++){
        int h = (rand() % (MAX_BUILDING_HEIGHT - MIN_BUILDING_HEIGHT + 1)) + MIN_BUILDING_HEIGHT;
        building_height[i] = h;
        city_record[i].height = h; // Set the height of the city to the building height
    }
    // 3. Draw city, landscape on the screen
    draw_landscape();
    draw_cities();
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
    return city_record[index];
}

/**
 * TODO:
 * Demolishes the specified city
 * @param index of the city to be demoolished,
 */
void city_demolish(int index) {
    ASSERT_P(index < MAX_NUM_CITY, ERROR_CITY_INDEX_DEMOLISH);

    if (city_record[index].status == EXIST) {
        // 1. grab original height
        int orig_h = city_record[index].height;

        // 2. compute our bottom/top in bottom-origin space
        int x0 = city_record[index].x;
        int y0 = city_record[index].y;
        int x1 = x0 + city_record[index].width - 1;
        int y1 = y0 + orig_h        - 1;   // top-edge of the building

        // 3. overdraw the entire rectangle
        uLCD.filled_rectangle(
            x0,
            REVERSE_Y(y0),  // bottom (converted)
            x1,
            REVERSE_Y(y1),  // top    (converted)
            BACKGROUND_COLOR
        );

        // 4. update status & clear data
        city_record[index].status = DEMOLISHED;
        city_record[index].height = 0;
        building_height[index]    = 0;
    }
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
   for(int i=0;i<MAX_NUM_CITY;i++){
      if(city_record[i].status == EXIST) {
        uLCD.filled_rectangle(city_record[i].x, REVERSE_Y(city_record[i].y),
          city_record[i].x+city_record[i].width-1, REVERSE_Y(city_record[i].y+city_record[i].height-1), CITY_COLOR);
      }
    }  
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
