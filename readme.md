
*i don't own the keyboard schematics nor actually design the pcb, this is only the firmware that i wrote for the board*

* Hardware Supported: *atmega32u4*
* firmware used: *qmk_firmware*


pins on ProMicro board : A3, A2, A1, A0, 16, 15, 14, 10, 9,  8,  7,  6,  1,  0
<br>
pins on atmega32u4     : F4, F5, F6, F7, B2, B1, B3, B6, B5, B4, E6, D7, D2, D3

HighSide (connected to source) = F4, F5, F6, F7, B1, B3, 
<br>
LowSide (connected to gnd)     = D3, D2, D7, E6, B2, B6, B5, B4, 

this keyboard has different matrix wiring, instead of 12x4 ortholinear it has 6x8 matrix

|layer 0| F4       | F5       | F6       | F7      | B1       | B3       |
| -- | -------- | -------- | -------- | ------- | -------- | -------- |
| D3 | KC\_TAB  | KC\_W    | KC\_R    | KC\_Y   | KC\_I    | KC\_P    |
| D2 | KC\_Q    | KC\_E    | KC\_T    | KC\_U   | KC\_O    | KC\_BSPC |
| D7 | KC\_ESC  | KC\_S    | KC\_F    | KC\_H   | KC\_K    | KC\_SCLN |
| E6 | KC\_A    | KC\_D    | KC\_G    | KC\_J   | KC\_L    | KC\_QUOT |
| B2 | KC\_LSFT | KC\_X    | KC\_V    | KC\_N   | KC\_COMM | KC\_SLSH |
| B6 | KC\_Z    | KC\_C    | KC\_B    | KC\_M   | KC\_DOT  | KC\_ENT  |
| B5 | KC\_LGUI | MO(1)    | KC\_LALT | KC\_SPC | MO(2)    | blank    |
| B4 | MO(2)    | KC\_LCTL | KC\_SPC  | MO(1)   | KC\_APP  | blank    |

|layer 1| F4       | F5       | F6       | F7       | B1       | B3       |
| -- | -------- | -------- | -------- | -------- | -------- | -------- |
| D3 | KC\_GRV  | KC\_2    | KC\_4    | KC\_6    | KC\_8    | KC\_0    |
| D2 | KC\_1    | KC\_3    | KC\_5    | KC\_7    | KC\_9    | KC\_BSPC |
| D7 | KC\_ESC  | KC\_BSPC | KC\_HOME | KC\_BSLS | KC\_RGHT | KC\_LBRC |
| E6 | KC\_DEL  | KC\_ENT  | KC\_END  | KC\_UP   | KC\_RCTL | KC\_RBRC |
| B2 | KC\_LSFT | KC\_PGDN | KC\_V    | KC\_LEFT | KC\_RALT | KC\_MINS |
| B6 | KC\_PGUP | KC\_C    | KC\_TAB  | KC\_DOWN | KC\_RSFT | KC\_EQL  |
| B5 | KC\_LGUI | KC\_BRIU | KC\_LALT | KC\_SPC  | KC\_TRNS | KC\_VOLD |
| B4 | KC\_BRID | KC\_LCTL | KC\_SPC  | KC\_TRNS | KC\_APP  | KC\_VOLU |

|layer 2| F4       | F5       | F6       | F7       | B1       | B3       |
| -- | -------- | -------- | -------- | -------- | -------- | -------- |
| D3 | KC\_F1   | KC\_F3   | KC\_F5   | KC\_F7   | KC\_F9   | KC\_F11  |
| D2 | KC\_F2   | KC\_F4   | KC\_F6   | KC\_F8   | KC\_F10  | KC\_F12  |
| D7 | KC\_ESC  | KC\_BSPC | KC\_NO   | KC\_NO   | MS\_RGHT | MS\_WHLU |
| E6 | KC\_DEL  | KC\_ENT  | KC\_NO   | MS\_UP   | MS\_BTN1 | KC\_BSPC |
| B2 | KC\_LSFT | KC\_PGDN | KC\_V    | MS\_LEFT | KC\_NO   | MS\_WHLD |
| B6 | KC\_PGUP | KC\_C    | KC\_HOME | MS\_DOWN | MS\_BTN2 | KC\_ENT  |
| B5 | KC\_LGUI | AG\_SWAP | KC\_LALT | KC\_SPC  | KC\_TRNS | QK\_RBT  |
| B4 | AG\_NORM | KC\_LCTL | KC\_END  | KC\_TRNS | DB\_TOGG | QK\_BOOT |



### Actual layout

| KC_TAB  | KC_Q   | KC_W   | KC_E   | KC_R   | KC_T   | KC_Y   | KC_U   | KC_I   | KC_O   | KC_P   | KC_BSPC |
|---------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|---------|
| KC_ESC  | KC_A   | KC_S   | KC_D   | KC_F   | KC_G   | KC_H   | KC_J   | KC_K   | KC_L   | KC_SCLN| KC_QUOT |
| KC_LSFT | KC_Z   | KC_X   | KC_C   | KC_V   | KC_B   | KC_N   | KC_M   | KC_COMM| KC_DOT | KC_SLSH| KC_ENT  |
| KC_LGUI | MO(2)  | MO(1)  | KC_LCTL| KC_LALT| KC_SPC | KC_SPC | MO(1)  | MO(2)  | KC_APP | blank  | blank   |

## Customizing the images/animations
convert images/gif each frame to 64x64 to bytes array with [image2cpp](https://javl.github.io/image2cpp/)
and replace the array in `keymap.c`

## Bootloader

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


## Compiling and Flashing the firmware

1. Install [QMK Firmware](https://docs.qmk.fm/#/newbs_getting_started) on your computer.
2. Create a directory named `kasep` in `qmk_firmware/keyboards/`.
3. Clone this repo to qmk_firmware/keyboards/kasep
4. cd qmk_firmware/keyboards/kasep/hd48ap
5. run qmk compile -kb kasep/hd48ap -km default
7. now you can flash the firmware with qmk toolbox or with avrdude
   * with qmk toolbox, open the .hex file that was created in step 6 and flash it
   * with avrdude, run this command (change the port accordingly):
     ```
     avrdude -p atmega32u4 -c avr109 -P /dev/ttyACM0 -b 57600 -U flash:w:hd48ap_default.hex
     ```

