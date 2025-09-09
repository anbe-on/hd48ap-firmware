
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
| B5 | KC\_LCTL | KC\_LGUI | KC\_LALT | KC\_SPC | TG(2)    | blank    |
| B4 | MO(1)    | KC\_LCTL | KC\_SPC  | TG(1)   | KC\_APP  | blank    |

|layer 1| F4       | F5       | F6       | F7       | B1       | B3       |
| -- | -------- | -------- | -------- | -------- | -------- | -------- |
| D3 | KC\_GRV  | KC\_2    | KC\_4    | KC\_6    | KC\_8    | KC\_0    |
| D2 | KC\_1    | KC\_3    | KC\_5    | KC\_7    | KC\_9    | KC\_BSPC |
| D7 | KC\_ESC  | KC\_BSPC | KC\_HOME | KC\_BSLS | KC\_RGHT | KC\_LBRC |
| E6 | KC\_DEL  | KC\_ENT  | KC\_END  | KC\_UP   | KC\_RCTL | KC\_RBRC |
| B2 | KC\_LSFT | KC\_PGDN | KC\_V    | KC\_LEFT | KC\_RALT | KC\_MINS |
| B6 | KC\_PGUP | KC\_C    | KC\_TAB  | KC\_DOWN | KC\_RSFT | KC\_EQL  |
| B5 | KC\_BRID | KC\_LGUI | KC\_LALT | KC\_SPC  | T0(0)    | KC\_VOLD |
| B4 | KC\_BRIU | KC\_LCTL | KC\_SPC  | T0(0)    | KC\_APP  | KC\_VOLU |

|layer 2| F4       | F5       | F6       | F7       | B1       | B3       |
| -- | -------- | -------- | -------- | -------- | -------- | -------- |
| D3 | KC\_F1   | KC\_F3   | KC\_F5   | KC\_F7   | KC\_F9   | KC\_F11  |
| D2 | KC\_F2   | KC\_F4   | KC\_F6   | KC\_F8   | KC\_F10  | KC\_F12  |
| D7 | KC\_ESC  | KC\_BSPC | KC\_NO   | KC\_NO   | MS\_RGHT | MS\_WHLU |
| E6 | KC\_DEL  | KC\_ENT  | KC\_NO   | MS\_UP   | MS\_BTN1 | KC\_BSPC |
| B2 | KC\_LSFT | KC\_PGDN | KC\_V    | MS\_LEFT | KC\_NO   | MS\_WHLD |
| B6 | KC\_PGUP | KC\_C    | KC\_HOME | MS\_DOWN | MS\_BTN2 | KC\_ENT  |
| B5 | AG\_NORM | KC\_LGUI | KC\_LALT | KC\_SPC  | T0(0)    | QK\_RBT  |
| B4 | AG\_SWAP | KC\_LCTL | KC\_END  | T0(0)    | DB\_TOGG | QK\_BOOT |


### Actual layout
```
           ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
           | TAB |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  | BSPC|
 ┌───────┐ ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 │ 128x64│ | ESC |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  | ;   | '   |
 └───────┘ ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   ┌───┐   | LSH |  Z  |  X  |  C  |  V  |  B  |  N  |  M  | ,   | .   | /xx | ENT |
   │ENC│   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   └───┘   | LCTL| MO1 | LGUI| LCTL| LALT| SPC | SPC | TG1 | TG2 | APP |MNNXT|MNPRV|
           └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
```

## Bootloader

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


## Compiling and Flashing the firmware

1. Install [QMK Firmware](https://docs.qmk.fm/#/newbs_getting_started).
2. Create a directory named `kasep` in `qmk_firmware/keyboards/`.
3. Clone this repo to qmk_firmware/keyboards/kasep
4. cd qmk_firmware/keyboards/kasep/hd48ap
5. run ```qmk compile -kb kasep/hd48ap -km default```
7. now you can flash the firmware with qmk toolbox or on terminal
   * first cd qmk_firmware/.build
   * with qmk toolbox, open the .hex file qmk_firmware/.build and then flash it
   * or on terminal:
     ```
     qmk flash kasep_hd48ap_default.hex
     ```

## Customizing the images/animations
convert images/gif each frame to 64x64 to bytes array with [image2cpp](https://javl.github.io/image2cpp/)
and replace the byte image image_frames in `keymap.c`

## Image byte editor

i've created a simple image byte editor to make it easier to edit the 64x64 image bytes array in imageEditor.py, it will loads the byte image automatically from the image_frames in keymap.c. 

Install the required Python packages:

```bash
pip install flask

# run it with:
python imageEditor.py
```

when saved it printed the frames directly into terminal that you can paste manually in the c code.
