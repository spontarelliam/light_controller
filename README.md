# light_controller
A light controller circuit for OWO.

This code uses an Arduino to read RFID tags. If the UID of the tag is in the solution set, an output is turned high and a timer starts counting. For the following three seconds, as long as the RFID tag remains in front of the reader, another output will go high each second, until 4 outputs are high. If the tag is removed from the reader at any time, all outputs go low.



# Wiring
I used a CAT5 cable to wire the RFID reader as follows,

Reader Pin | Wire color | Arduino Pin
SDA | GRN | D10
SCK | GRN/WHT | D13
MOSI | BRN | D11
MISO | BRN/WHT | D12
GND | ORG/WHT | GND
RST | BLUE | D9
3.3V | BLUE/WHT | 3.3V

The output pins are wired as follows,
Output 1 | D3
Output 2 | D4
Output 3 | D5
Output 4 | D6
