# LED Matrix

A simple 8 by 8 LED matrix made from easy-to-find Neopixel LED strips, 
adhered to a laser-cut baseboard, and mounted in a 3D printed case. 

Control is provided by an ESP32 microcontroller. Code written in the 
Arduino IDE. 

### Materials

- 1 x ESP32 Devkit V1
- 1 x MAX9814 Module
- 1 x WS2812 LED Strip (64 LEDs, 60 Pixel/meter)
- 1 x 1/16th inch wood board (at least 5"x5") 
- 8 x M2 heat-set threaded inserts
- 4 x M3 heat-set threaded inserts
- 4 x M2 x 4mm screws 
- 4 x M2 x 6mm screws
- 4 x M3 x 6mm screws
- 4 x 6mm x 2mm neodymium magnets 
- 1 x Parchment paper or other thin light diffuser
- 1 x 4cm x 6cm universal proto-board
- 1 x 5 pin 2.54mm female header 
- 2 x 20 pin 2.54mm female header
- 1 x JST Female Connector
- 1 x JST Male Connector
- 1 x USB-A to micro-USB type B cable (with data lines)
 
##### Additional requirements 
- 3D printer
- Soldering iron
- Solder
- Super glue
- Hot glue

### Assembly instructions
_Photos to come_

1. Print the base, cover and back. STL files can be found [here](02_mechanical)
2. Using a soldering iron, insert the 4 M3 heat-set inserts into the outer 
threaded insert holes. Insert the 8 M2 heat-set inserts into the remaining 
holes. 
3. Cut out the LED board, with dimensions matching those in the CAD file, 
or use a laser cutter. 
4. Cut the LED strip into sections of 8, cutting down the center of the 
copper pads. 
5. Use the silicone wire to solder the individual LED strips. Make sure 
the wire is the length of the LED board, plus perhaps an extra inch. Make 
sure that the DOUT pad of each LED strip connects the DIN pad of the 
next strip. DO NOT connect a DIN pad to DIN, or a DOUT pad to DOUT.  
6. Attach the LEDs to the board, by removing the thin plastic backing and 
attaching them to the board, using the adhesive on the strip. Then use 
little touches of hot glue around the edges of the board, to prevent the 
LED strip from peeling off, and to cover the exposed wire and copper pads. 
7. To the last LED strip, solder on a JST connector. 
8. Solder 18 pin female header pins to the proto board. For the microphone, 
add a 5 pin female header pin.
9. Solder a JST connector to the proto-board. (Must be able to connect 
to the corresponding connector attached to the LED strip). Connect 5v to 
the ESP32 VIN pin. Connect ground to GND. Connect DIN to pin D13 (At least 
if you want to be consistent with the demo code. 
10. Solder connections for the MAX9814 header pin. Make sure that V+ is 
connected to the ESP32 3v3 pin, GND is connected to GND, and to be 
consistent with the demo code, connect Out to D32, G (gain) to D5, and AR 
to D22. 
11. Screw the proto-board to case. Insert the ESP32 board into the female 
header pins. Insert the MAX9814 to the corresponding header pins. 
12. Connect the JST connector from the proto board to the LED strips. 
13. Glue magnets to the exterior of the case, and the interior of the cover. 
Ensure that the magnets are orientated such that when the cover is placed 
onto the case, the magnets attract each other and do not repel each other. 
14. Cut a strip of your parchment paper or other diffuser material, using 
the front of the base as a guide. You can leave a little room around the
edges to make sure that the diffuser material covers the entire grid case. 
15. Place the diffuser on the base, then put the cover over it. 
16. Screw the back to the case. 

