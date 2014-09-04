#include <TempController.h>

//We always have to include the library
#include "LedControl.h"

int ledlist[] = { LED_A_BLUE, LED_A_RED, LED_B_BLUE, LED_B_RED };

#if 0
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 13 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 12 is connected to LOAD 
 We have only a single MAX72XX.
 */
 
#define LC_DIN (13)
#define LC_CLK (11)
#define LC_LOAD (12)
#endif
// LedControl(DataIn, CLK, Load, number-of-max72xx)

LedControl lc=LedControl(LC_DIN, LC_CLK, LC_LOAD, 1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;
unsigned int count = 0;

void setup() {
    Serial.begin(9600);

  Serial.println("Setup");
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void countdelay(unsigned long time) {
  lc.setRow(0, 3, ledlist[count & 3]);
  delay(time);
  count++;
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment(int digit) {
  lc.setChar(0,digit,'a',false);
  countdelay(delaytime);
  lc.setRow(0,digit,0x05);
  countdelay(delaytime);
  lc.setChar(0,digit,'d',false);
  countdelay(delaytime);
  lc.setRow(0,digit,0x1c);
  countdelay(delaytime);
  lc.setRow(0,digit,B00010000);
  countdelay(delaytime);
  lc.setRow(0,digit,0x15);
  countdelay(delaytime);
  lc.setRow(0,digit,0x1D);
  countdelay(delaytime);
  lc.clearDisplay(0);
  countdelay(delaytime);
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=15;i>=0;i--) {
    lc.setDigit(0,7,i,false);
    lc.setDigit(0,6,i-1,false);
    lc.setDigit(0,5,i-2,false);
    lc.setDigit(0,4,i-3,false);
    countdelay(delaytime);
  }
  lc.clearDisplay(0);
//  countdelay(delaytime);
}

void loop() { 
  writeArduinoOn7Segment(7);
  scrollDigits();
}
