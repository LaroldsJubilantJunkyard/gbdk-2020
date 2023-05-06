#include <gb/gb.h>
#include <stdint.h>
#include "player.h"
#include "common.h"
#include "level.h"
#include "Camera.h"

void main(void)
{
	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;

    // Make sure these are initially different so the "setupcurrentLevel" logic is triggered
    currentLevel=255;
    nextLevel=0;

    // Loop forever
    while(1) {

        // if we want to change levels
        if(nextLevel!=currentLevel){

            // Update what our current level is
            currentLevel=nextLevel;

            // Setup the new level
            SetupCurrentLevel();

            // Make the initial draw for the camera
            InitialCameraDraw();

            // Setup the player
            SetupPlayer();
        }

        // Get the joypad input
        joypadPrevious = joypadCurrent;
        joypadCurrent = joypad();

        UpdatePlayer();
        UpdateCamera();

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
