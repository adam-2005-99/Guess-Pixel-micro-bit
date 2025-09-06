#include "MicroBit.h"
#include "samples/Tests.h"

MicroBit uBit;

// To recieve selected coordenates
PacketBuffer b(2);

// Coordinates of the cursor
int cursorI = 0, cursorJ = 0;

// Move the cursor to the right
void onButtonB(MicroBitEvent e){
    uBit.display.image.setPixelValue(cursorJ, cursorI, 0);

    if(cursorJ >= 4){
        if(cursorI >= 4){
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }else{
            cursorJ = 0;
            cursorI++;
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }
    }else{
        cursorJ++;
        uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
    }
}

// Move cursor to the left
void onButtonA(MicroBitEvent e){
    uBit.display.image.setPixelValue(cursorJ, cursorI, 0);
    if(cursorJ <= 0){
        if(cursorI <= 0){
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }else{
            cursorJ = 4;
            cursorI--;
            uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
        }
    }else{
        cursorJ--;
        uBit.display.image.setPixelValue(cursorJ, cursorI, 255);
    }
}

// When button AB clicked send the cursor coordinates
void onButtonAB(MicroBitEvent e){
  
    b[0] = cursorJ;
    b[1] = cursorI;
    
    uBit.radio.datagram.send(b); 
}

// Recieve the the guesed pixels by the second player 
void onData(MicroBitEvent e){
    
    b = uBit.radio.datagram.recv();
    cursorJ = b[0];
    cursorI = b[1];
    uBit.display.image.setPixelValue(cursorJ, cursorI, 100);

}


int main()
{
    uBit.init();
    uBit.radio.enable();
    uBit.radio.setGroup(6);


    uBit.display.image.setPixelValue(cursorJ, cursorI, 255);

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButtonAB);
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

    


    release_fiber();
}



