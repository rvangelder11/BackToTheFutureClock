# Assembly instructions

- Print the 3D parts. On my Ender 3 it just fitted if I printed it at almost 45 degrees without a skirt.
- Glue the pieces together (I used Bisontix, but other glue might work as well).
- The bottom part has a tight fit, to prevent falling out.

![PCB_PCB_BTTF print_2_2023-05-01](https://github.com/rvangelder11/BackToTheFutureClock/assets/90907092/c57c9c1c-cdd8-42f8-bd20-cabfd743ef32)

![Schematic_BTTF print_2023-05-01](https://github.com/rvangelder11/BackToTheFutureClock/assets/90907092/17cd4809-5033-4a8a-8375-b1c729c7a8dc)

The PCB is suitable for all three levels. By connecting to the right connector, the right LED signals are transfered.

- The bottom level PCB needs to be populated with the power connector DC1, femail pin headers for the microcomputer ESP32-S2 (assuming that the microcomputer contains the female pins). In my version of the PCB, these pins were a bit to close together, so the ESP32 needed a little squeeze to fit. 
- each PCB contains on the frontside (the side that shows "LED Display" and "Segment") from left to right: two 4 digit numeric display, a 4 digit alphanumeric display and one 4 digit display. The 4 digit displays have 4 pins on each side. The female part is mounted on the PCB, the male part on the display. The alphanumeric display has 5 pins on the top, again with pins on the display side and female parts on the PCB side.
- The bottom PC contains all displays in Orange
- AM and PM leds are between the two left 4 digit displays. Resistor value 330 ohm.
- For the bottom PC, 2x17 pins need to be soldered on the backside of the PC at the location indicated with "ALL". the two left most round holes are not used
- Also on on the backside, an LM2596 buck converter needs to be mounted to reduce the incoming voltage. Before anything else is connected, check whether the output voltage is 5V
- The middle PCB is only populated with the yellowgreen displays, resistors and green LEDS  and on the backside with 2x18 pins on the position indicated with "GREEN"
- The top PCB is only populated with the red displays and on the backside with 2x17 pins on the position indicated with "GREEN". the two left most round holes are not used
- I have added a switch to be able to swith between 3.3V or 5V to the numeric displays. I found that it needs to be at 3.3V at startup. When all displays are on (and the time is synchronised) you can switch to 5V to have the right brightness. The switch is wired to the bottom PC at location indicated with S1

## With the flatcable connected

![IMG_0111](https://github.com/rvangelder11/BackToTheFutureClock/assets/90907092/a93c814a-46e3-4ac3-8f5e-46f209fb75dc)

## Without the flatcable

![IMG_0112](https://github.com/rvangelder11/BackToTheFutureClock/assets/90907092/58932d8b-a3e1-4f3e-8246-840ef52f8dfc)
