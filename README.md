# Main functions
* Atari DIN13 to VGA
* 3.5mm A/V connector with volume control.
* Automatic detection of resolution.

# Manual
Plug device into your Atari.
Turn your Atari on.
Press .25-1.999[...] seconds: Switch mode.
Press +2 seconds: store current mode as default at cold boot.

# Assebly tips
For least amount of wobbliness:
1. Backside SMD stuff (TS5V330, ATtiny85 and 78l05). 
2. Flip board over, solder all SMD.
3. DIN13
4. Lastly solder volume pot and VGA. Flipping of board is optional if you're a good at soldering.

# BOM
Part|Value|Device|Package|Description|MF|MPN|OC_FARNELL|OC_NEWARK|PACKAGE|PROD_ID|SUPPLIER|
--|--|----|----|---|--|---|-|-|-|-|-|
ATARIOUT|DIN13T|DIN13T|DIN13|||||||||
IC2|78L05F|78L05F|SOT89|POSITOIV-VOLTAGE REGULATORS||||||||
JP1||PINHD-1X2|1X02|PIN HEADER||||||||
S1|SWITCH-MOMENTARY-2TACTILE-SWITCH-SMD-RIGHT-ANGLE|SWITCH-MOMENTARY-2TACTILE-SWITCH-SMD-RIGHT-ANGLE|TACTILE_SWITCH-SMD-RIGHT-ANGLE|Various NO switches- pushbuttons, reed, etc||||||COMP-12265||
TM1||TRIMPOTTC33X|TC33X|SMT trimmer potentiometer part number TC33X||||||||
TM2||TRIMPOTTC33X|TC33X|SMT trimmer potentiometer part number TC33X||||||||
TM3||TRIMPOTTC33X|TC33X|SMT trimmer potentiometer part number TC33X||||||||
TS5V330||V330|SOIC16N|||||||||
U$1|AUDIO-JACK3|AUDIO-JACK3|AUDIO-JACK-TRRS-SMD|Audio jack - 3.5mm TRRS variety - two rings.||||||CONN-10676||
U$2|DB-1001N|DB-1001N|THUMB_POT|Multicomp||||||||
U1|ATTINY85-20SU|ATTINY85-20SU|SOIC127P798X216-8N|8-bit Microcontroller with In-System Programmable Flash||ATTINY85-20SU|1455164|58M3797|SOIC-8||Atmel|
X1||F15HDVS|HDF15V|SUB-D|||unknown|unknown||||


# Troubleshooting
 Symptom        | Solution|
| ------------- |:------|
|Constant switching|Check ATtiny soldering, probably rebooting. +5V and GND are possible offenders.|
|Dark picture.|Check soldering on multiplexer, pin 8 and 16 (GND and VCC).|
|Physical switch not working, software switching works.| Check soldering at ATtiny PB4 and soldering at the tactile switch itself.|
|Niether software or hardware switching works.| Check soldering ATtiny PB3 and multiplexer pin 1.|
|Niether software or hardware switching works, boots in low res.| Did you remember to program your ATtiny?|
|Software switch not working|Check soldering on ATtiny PB2 and V-sync on DIN|
|Hardware switch slow.|Did you set fuses ("Burn bootloader" in Arduino IDE) before programming ATtiny? Processor is probably running in 1MHz.|
