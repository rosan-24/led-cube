# 4x4x4 LED Cube (led-cube)

## About the project

A 4x4x4 LED cube (64 LEDs) powered by an ESP32 DEVKITV1. It runs from a single LiPo cell, with a charger and a boost converter on the board.

The main board is a two-layer PCB, 90.05 x 90.05 mm, 1.6 mm thick. The 64 LEDs and the cube frame are wired off the board.

This is a learning project. KiCad is new to me, so the design went through several rounds of fixes.

**Status:** schematic done, PCB routed, gerbers generated. Not yet built or tested.

---

## BOM

Prices are not filled in yet.

| sno | part | description | qty |
|---|---|---|---|
| 1 | ESP32 DEVKITV1 (30-pin) | Brain of the cube, runs the firmware | 1 |
| 2 | TP4056 charger module | Charges the LiPo cell over USB | 1 |
| 3 | 7Semi TPS61023 boost module | Boosts 3.7 V to 5 V for the ESP32 VIN | 1 |
| 4 | LiPo cell, 3.7 V | Powers the cube | 1 |
| 5 | Resistor, 220 ohm | Layer resistors R1 to R4 | 4 |
| 6 | Power switch SW1 | Turns the cube on and off (see Known issues) | 1 |
| 7 | 4-pin connector LI1, 4.8 mm pitch | Layer wires to the cube | 1 |
| 8 | Column pads L1 to L16 | Column wires to the cube (0.5 mm solder wire) | 16 |
| 9 | LED choose blue or red for better experince  | Cube LEDs, wired off the board | 64 |
| 10 | Enclosure | 3D printed, from `Enclosure.stl` | 1 |

---

## Project workflow

The full build log is in [JOURNAL.md](JOURNAL.md).

- **Nov 7:** Gathered the parts and started the schematic. Made the ESP32 DevKit symbol and the TPS61023 symbol, since neither was in the library.
- **Nov 11:** Finished the footprints for the ESP32, boost and charger, and reworked the schematic.
- **Nov 13:** Routed the wires with the right track width for each net, and used both copper layers.
- **Nov 16:** Designed the enclosure in Onshape.
- **Nov 18:** Routed the PCB and fixed the schematic and PCB design errors.
- **Nov 22:** Organized the LED layers, checked the connections, and added a hole for the ESP32 and text on the board.

---

## Schematic and PCB

**Schematic:** the ESP32 DevKit, TP4056 charger, TPS61023 boost, power switch, 4 layer resistors, the layer connector LI1 and 16 column pads.

**Power path:** LiPo cell to the TP4056 battery pads, then TP4056 OUT+ through SW1 to the boost input. The boost output (5 V) feeds the ESP32 VIN pin. All grounds are shared.

**PCB:**
- Two copper layers (F.Cu and B.Cu), 131 tracks,0 vias,0 copper pours.
- Track widths: 0.3 mm for LED layer and column nets, 0.5 mm for GND and VIN, 1.0 mm for the battery side.
- All 29 nets are fully routed.
- The gerbers in `Gerber.zip` match the current PCB.

---

## Pin map

Columns L1 to L16, one GPIO each, no resistor
Layers LI1 pins 1 to 4, each through a 220 ohm resistor
---

## Features

- 64 LEDs in four layers of 16 columns.
- Runs from a LiPo cell, with USB charging.
- Planned firmware

---
## How to build

- **Step 1:** Check you have all the parts from the BOM.
- **Step 2:** Then order the PCB from `Gerber.zip`.
- **Step 3:** Print the enclosure from `Enclosure.stl`.
- **Step 4:** Solder the parts, connect the battery and the cube wiring, and check every column and layer by hand.
- **Step 5:** Flash the firmware once it's added to the repo.



---

## Contributors

- [@rosan-24](https://github.com/rosan-24)

---

## Resources

- [JOURNAL.md](JOURNAL.md): full build log, November 7 to 22, 2026.

---

## Special credits

- The build log is written for Hack Club Fabricate.

---

## License
.--. .-. .. ...
    ~rosh
     
