# kasep/hd48ap

*i don't own the keyboard schematics, this is only the firmware that i wrote for the board*

* Hardware Supported: *atmega32u4*

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## README work in progress
