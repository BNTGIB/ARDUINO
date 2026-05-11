# 📦 The Emotional Useless Box
A Useless Box with diverse "personalities", driven by an array of function pointers.

## Introduction
The Useless Box DIY project features a push-pull linkage mechanism enabling an active lid slam, combined with randomized behavioral scripts to express various emotional states (Normal, Angry, Shy, etc.).

## Features
- Active lid mechanism powered by an independent servo.
- RGB LED indicator for emotional states.
- Randomized emotional state system.

## Hardware Requirements
- 1x Microcontroller (Arduino NANO).
- 2x Micro Servo SG90.
- 1x MTS 2-Way Toggle Switch.
- 1x 18650 Battery + TP4056 Charging Module.
- 1x Mini Boost Converter (for Arduino).
- Case Material: 3mm Formex.

## Mechanical Blueprint
![Case Blueprint](Formex_layout.png)

## Installation
1. Clone this repository to your local machine.
2. Open the `.ino` file using Arduino IDE.
3. Ensure the `Servo.h` library is installed (built-in with the IDE).
4. Upload the code to the board.

## Roadmap (TODO)
- [x] Design Formex case dimensions.
- [x] Measure, cut Formex, and assemble the case.
- [x] Hardware processing: wiring and soldering components.
- [ ] Mount hardware components into the case and test basic functions.
- [ ] Write and test the core source code for the project.
- [ ] Finalize the array of function pointers for behavioral scripts.

## Hardware Setup & Troubleshooting

During the physical assembly process (Formex cutting, soldering, wiring), the project encountered several physical issues which were resolved using the following "hotfix" techniques:

### 1. Material & Aesthetics: Structural Weakness
* **Issue:** When cutting the Formex based on the initial design, the 120x100mm base made of 3mm Formex proved too flimsy. The same applied to the front/back panels and the lid section where hardware components are mounted.
* **Solution:** Reinforced the weak areas by gluing an additional Formex layer, increasing the thickness to 6mm. Modified the case design to be wider, allowing the side panels to overlap and hide the base cut lines for a cleaner aesthetic.

### 2. Mechanical: Toggle Switch Anti-Rotation on Formex
* **Issue:** Formex has a soft, porous surface. Tightening the nut alone allows the switch to rotate during continuous use.
* **Solution:** Applied a reverse assembly order: `Toothed Washer`  -> `Keyed Washer` (teeth facing upwards). Upon tightening the nut, the keyed washer's sharp teeth bite and sink deeply into the Formex, creating a perfect anti-rotation lock.

### 3. Circuit Salvage (Hardware Bypass): Torn TP4056 Pad
* **Issue:** Due to poor initial soldering, the `OUT-` copper pad on the TP4056 module was completely ripped off.
* **Solution:** Traced the copper line connected to `OUT-`, used a sharp tool to gently scrape off the blue solder mask along that trace to expose the shiny copper underneath, and soldered the wire directly to that exposed area. Applied UHU glue over the joint (Strain Relief technique) to lock the wire to the PCB and prevent physical pulling from ripping the IC pins.

### 4. Firmware: `not in sync: resp=0x00` Error
* **Issue:** Arduino IDE failed to communicate with the chip during upload.
* **Solution:** The Nano board uses a legacy bootloader. Fixed by selecting `Tools > Processor > ATmega328P (Old Bootloader)`.

### 5. Logic Inversion: Software Fixing Hardware
* **Issue:** Soldered the wire to the top terminal instead of the bottom terminal of the toggle switch, resulting in inverted physical logic (Switch UP = Open circuit, Switch DOWN = Closed circuit).
* **Solution:** Utilized the internal `INPUT_PULLUP` resistor and inverted the logic in the code. Open circuit = `HIGH` (Box Active), Closed circuit = `LOW` (Box Sleep). Avoided the need to desolder physically.

---

## [Hardware Test Code](Hardware_Test/Hardware_Test.ino)