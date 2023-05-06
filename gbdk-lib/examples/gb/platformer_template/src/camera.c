
#include <stdint.h>
#include <gbdk/platform.h>
#include "level.h"

#include <gb/gb.h>
#include <stdint.h>

#define MIN(A,B) ((A)<(B)?(A):(B))

// current and old positions of the camera in pixels
uint16_t camera_x, camera_y, old_camera_x, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;
// redraw flag, indicates that camera position was changed
uint8_t redraw;

void UpdateCamera(){

    // update hardware scroll position
    SCY_REG = camera_y; SCX_REG = camera_x; 
    // up or down
    map_pos_y = (uint8_t)(camera_y >> 3u);
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            set_bkg_submap(map_pos_x, map_pos_y, MIN(21u, currentLevelWidthInTiles-map_pos_x), 1, currentLevelMap, currentLevelWidthInTiles);
        } else {
            if ((currentLevelHeightInTiles - 18u) > map_pos_y) set_bkg_submap(map_pos_x, map_pos_y + 18u, MIN(21u, currentLevelWidthInTiles-map_pos_x), 1, currentLevelMap, currentLevelWidthInTiles);     
        }
        old_map_pos_y = map_pos_y; 
    }
    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);
    if (map_pos_x != old_map_pos_x) {
        if (camera_x < old_camera_x) {
            set_bkg_submap(map_pos_x, map_pos_y, 1, MIN(19u, currentLevelHeightInTiles - map_pos_y), currentLevelMap, currentLevelWidthInTiles);     
        } else {
            if ((currentLevelWidthInTiles - 20u) > map_pos_x) set_bkg_submap(map_pos_x + 20u, map_pos_y, 1, MIN(19u, currentLevelHeightInTiles - map_pos_y), currentLevelMap, currentLevelWidthInTiles);     
        }
        old_map_pos_x = map_pos_x;
    }
    // set old camera position to current camera position
    old_camera_x = camera_x, old_camera_y = camera_y;
}

void InitialCameraDraw(){

    set_bkg_submap(0,0,21,18,currentLevelMap,currentLevelWidthInTiles);
}


