
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
void city_demolish(int index){
#ifdef F_DEBUG
  pc.printf("[F] city_demolish()\r\n");
#endif 

    // Error checking - index must be within max
    ASSERT_P(index<MAX_NUM_CITY,ERROR_CITY_INDEX_DEMOLISH);

 if (city_record[index].status == EXIST) {
        // 1. Remove the city
        building_height[index]    = 0;
        city_record[index].height = 0;

        // 2. Update the status of all that has happened
        city_record[index].status = DEMOLISHED;

        // 3. Erase the city graphic
        uLCD.filled_rectangle(
            city_record[index].x,
            city_record[index].y,
            city_record[index].x + city_record[index].width - 1,
            city_record[index].y - city_record[index].height + 1,
            LANDSCAPE_COLOR
        );
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
