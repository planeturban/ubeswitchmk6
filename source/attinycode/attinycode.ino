/*
   Compiled with MicroCore: 980 bytes. (Not working..)
   Compiled for Attiny85: 956 bytes.
                          5244 bytes with debug.
How to read this code:
1. Don't. It's ugly.
2. When "pin" is referred in code (or text) it's the Atari side of things. The ATtiny's pins are always referred to as PBX. 

*/


//#define LEGACY // Uncomment this if your device does not have a ISP header.
//#define ALT_DETECT





//#define DEBUG


// Timings.
#define switchTime 250000
#define saveTime 2000000
#define bootWait 4000 // Wait for computer to stabilize, 3-4s seems ok.





#include <EEPROM.h>




#if defined(DEBUG) && !defined(LEGACY)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(PB0, PB1); // RX, TX
#endif



#ifdef LEGACY
#define buttonPin PB0       // Connected to switch
#define selectPin PB1     // TS5V330 pin 1
#define pulsePin PB2       // VSync
#else
#define pulsePin PB2       // VSync
#define selectPin PB3     // TS5V330 pin 1
#define buttonPin PB4       // Connected to switch
#endif



unsigned long buttonPressedTime;
int pulseThreshold = 15000;

byte state;
byte lastState;
byte tosState;

#ifdef DEBUG
bool done = false;
String buff;
char data;
int i = 0;
#endif

unsigned long pulse = 0;


void setup() {
// IDEA: check if a jumper is placed on the ISP header to enter some kind of other operations mode. 


#if defined (DEBUG) && !defined(LEGACY)
  mySerial.begin(9600);
  mySerial.println("Boot");
#endif

  PORTB |= bit(buttonPin); // Input pullup.

  state = EEPROM.read(0);
// Instead of sending +5V to the Atari, let the pullup on pin4 handle the high part.
  bitWrite(DDRB, selectPin, state); 


#if defined (DEBUG) && !defined(LEGACY)
  mySerial.print("Waiting for ");
  mySerial.print(bootWait);
  mySerial.println(" milliseconds.");
#endif
  _delay_ms(bootWait);
  lastState = state;
#if defined (DEBUG) && !defined(LEGACY)
  if ( ! bitRead(PINB, buttonPin) )
    mySerial.println("Button held, prompt...");

  mySerial.print("> ");

/*
// Really need to fix this part.
  while ( ! done ) {
    if ( mySerial.available() > 0 ) {
      data = mySerial.read();
      mySerial.print(data);
      if ( int(data) != 10 ) {
        buff[i] = data;
        i++;
      } else {
        if ( buff[0] == "q" ) {
          done = true;
        } else if ( buff[0] == "h" ) {
          printHelp();
          clearBuff();
        } else if ( buff[0] == "b" ) {
          PORTB ^= bit(selectPin);
          clearBuff();
        } else if ( buff[0] == "s" ) {
          if ( buff[2] == " " )
            buff = buff.substring(2);
          else
            buff = buff.substring(1);
          int v = buff.toInt();
          clearBuff();
        } else {

          mySerial.println("Error in command.");
        }
      }
    }

  }
*/

    while ( ! bitRead(PINB, buttonPin) ); // Wait for button to be released.


  mySerial.println("Loop.");
#endif



}




#ifdef DEBUG
void clearBuff() {
  buff = "";
  i = 0;
  mySerial.print("> ");
}



void printHelp() {
  mySerial.println("Help");
  mySerial.println("-----------");
  mySerial.println("b       - Simulate button press.");
  mySerial.println("p       - Print information.");
  mySerial.println("q       - Quit prompt.");
  mySerial.println("s <num> - Set pulse threashold.");

}
#endif

void loop() {

  /*
     Detection..
  */
  pulse = 0;
#ifdef ALT_DETECT
  while ( pulse < 10000 ) // 10000 since sometimes you'd get 14 from getPulse();
    pulse = getPulse();
#else

  while ( ! pulse )
    pulse = pulseIn(pulsePin, HIGH, 1000000L);
#endif


  state = pulse < pulseThreshold;



  if ( state != lastState ) {
#if defined (DEBUG) && !defined(LEGACY)
    mySerial.println("State change");
    mySerial.print("New state: ");
    mySerial.println(state);
    mySerial.print("Pulse: ");
    mySerial.println(pulse);
#endif
    bitWrite(DDRB, selectPin, state);

  }
  lastState = state;

  /*
       Button, save and switch.
  */

  if ( !bitRead(PINB, buttonPin) ) {
    buttonPressedTime = micros();
    while ( ! bitRead(PINB, buttonPin)); // Ugly debounce
    if ( micros() > saveTime  + buttonPressedTime ) {
#if defined (DEBUG) && !defined(LEGACY)
      mySerial.println("Save");
      mySerial.print("Value: ");
      mySerial.println(state);
#endif
      EEPROM.write(0, state);
    } else if ( micros() > buttonPressedTime + switchTime ) {
#if defined (DEBUG) && !defined(LEGACY)
      mySerial.println("Switch");
#endif
      DDRB ^= bit(selectPin);

      _delay_ms(1000); // Wait for computer to reboot and get its shit togheter.
    }
  }
}

unsigned long getPulse() {
  pulse = bitRead(PINB, pulsePin);
  while ( bitRead(PINB, pulsePin) == pulse);
  unsigned long pstart = micros();
  while ( bitRead(PINB, pulsePin) != pulse);
  return ( micros() - pstart);
}






