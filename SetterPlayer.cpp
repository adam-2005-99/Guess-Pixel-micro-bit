#include "MicroBit.h"
#include "samples/Tests.h"

MicroBit uBit;

PacketBuffer b(3);

// coordinates of the selected pixel
int selectedI = -1, selectedJ = -1;
// coordinates of the cursor
int cursorI = 0, cursorJ = 0;



/*
* Clear screen
* Reset all coordinates
*/
void resetGame(){
    // clear screen 
    uBit.display.image.clear();

    // reset i, j, selectedI, selectedJ
    cursorI = cursorJ = 0;
    b[0] = b[1] = b[3] = selectedI = selectedJ = -1;
    uBit.display.image.setPixelValue(cursorJ, cursorI, 255);

}


// Move the cursor to the right
void onButtonB(MicroBitEvent e){
    uBit.display.image.clear();
    uBit.display.image.setPixelValue(selectedJ, selectedI, 255);
    if(cursorJ >= 4){
        if(cursorI >= 4)
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        else{
            cursorJ = 0;
            cursorI++;
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }
    }
    else{
        cursorJ++; 
        uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
    }
}

// Move the cursor to the left
void onButtonA(MicroBitEvent e){
    uBit.display.image.clear();
    uBit.display.image.setPixelValue(selectedJ, selectedI, 255);
    if(cursorJ <= 0){
        if(cursorI <= 0)
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        else{
            cursorJ = 4;
            cursorI--;
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }
    }
    else{
        cursorJ--; 
        uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
    }
}




/*
* Select the pixel with one click
* Click again to send the coordinates
*/
void onButtonAB(MicroBitEvent e){
    // If the coordinates are stroed in the Selected I & J send coordinates to the next player
    if (selectedJ == cursorJ && selectedI == cursorI) {
        b[0] = cursorJ;
        b[1] = cursorI;
        
        uBit.radio.datagram.send(b);
        uBit.display.scroll("T"); 
        uBit.audio.setVolume(50); 
        uBit.audio.soundExpressions.play("happy");
        uBit.display.image.setPixelValue(selectedJ, selectedI, 255);

    } else {
        // Store cursor coordinates
        selectedJ = cursorJ;
        selectedI = cursorI;
        uBit.display.image.setPixelValue(selectedJ, selectedI, 255); 
    }
}

/*
* Revieve the selected coordinates by the other player
* Light the selected pixel
*/
void onData(MicroBitEvent e)
{
    b = uBit.radio.datagram.recv();
    if(b[2] == 1){
        resetGame();
        return;
    }
    cursorJ = b[0];
    cursorI = b[1];
    uBit.display.image.setPixelValue(cursorJ, cursorI, 10);
}


int main()
{
    // Initialise the micro:bit
    uBit.init();
   
    uBit.radio.enable();
    uBit.radio.setGroup(6);


    uBit.display.image.setPixelValue(cursorJ, cursorI, 255);

    // Set up listeners for button A, B and the combination A and B.
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButtonAB);

    // Set up a listener for the radio
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

   

    release_fiber();
}

