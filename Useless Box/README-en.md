# 📦 The Emotional Useless Box
A Useless Box with diverse "personalities", driven by an array of function pointers.
<video controls src="Product_Video.mp4" title="Title"></video>

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
- [x] Mount hardware components into the case and test basic functions.
- [x] Write and test the core source code for the project.
- [x] Finalize the array of function pointers for behavioral scripts.

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

## Project Structure & Modularization
The project follows a modular architecture by splitting the source code into `3 main tabs` (files) within the Arduino IDE. This approach simplifies logic management by decoupling hardware configurations from behavioral scripts.

| Tab / File       | Role | Key Functions                                                                                                                        |
| :--------------- | :------------: | :------------------------------------------------------------------------------------------------------------------------------------- |
| `UselessBox.ino` |  **Director**  | Manages the main flow (setup & loop), global variables, and coordinates behaviors using a Function Pointer Array.                      |
| `Hardware.ino`   | **Backstage**  | Low-level hardware abstraction, including RGB LED control, Switch state reading, and Servo positioning.                                |
| `Animations.ino` |   **Actor**    | A collection of "emotional" scripts (Angry, Shy, Troll, Normal...). Each function represents a unique personality trait of the device. |

### Why Modularize?
- Scalability: To add a new behavior (e.g., actionCrazy), I only need to define a new function in the Animations tab without cluttering the core logic or hardware drivers.

- Educational Value: This structure provides hands-on experience with Variable Scope management (Global vs. Local) and file linking within the C/C++ environment.

- Clean Code: Keeps the primary file concise, readable, and focused on high-level decision-making.

## Core Logic & Features
The central program of the device is referred to as the "Box".

### 1. The Emotion Engine (Stress Mechanism)
Unlike standard Useless Boxes that play random sequences, this box tracks user behavior. 
- The Box utilizes a `stressLevel` variable (ranging from 0 to 10), which increases if the switch is toggled again within 5 seconds of the previous interaction.
- If left undisturbed, the Box will "calm down," gradually decreasing its stressLevel

### 2. Dynamic Action Selection
An array contains multiple function pointers, each representing a specific toggle action with unique characteristics and reaction intensities (e.g., Normal, Angry). The `loop()` function selects the array index—and thus the reaction—based on the current `stressLevel`.
- Low stress: Triggers basic, slow animations.
- High Stress: Triggers reactions that are stronger, faster, multi-step, and more erratic.
- **"The Velvet Glove":** There is a 10% chance for the BOX to perform a "gentle" action even when at High Stress. This mimics the unpredictable nature of human emotions.
- **"The Death Stare":** If the Box is at a medium stress level `(stressLevel >= 5)`, there is a `33%` chance it will pop the lid open after toggling the switch to **"glare"** at or **"threaten"** the user. This acts as a warning through the `Watch_Out_For_Me()` function.
### 3. Smooth Hardware Abstraction
To make the servo movements appear more natural, two wrapper functions were added: `finger(val, speed)` and `cover(val, speed)`.
- Instead of simply snapping to the target angle, these functions calculate the current position using `.read()` and use a `for` loop to rotate steadily toward the destination.
- The rotation speed is adjustable via the `speed` parameter, allowing for precise control over the movement's positioning and pace
