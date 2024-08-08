# Arduino Memory Game Project

This project is a simple memory game built using an Arduino. The game challenges players to remember and replicate a sequence of LED flashes, with each correct replication extending the sequence.

## Thanks to fred for the Source code

**This project is for educational purposes. Make sure to use it responsibly and in environments that are safe for such electronic projects.**

## Features

- Interactive memory game with increasing difficulty.
- Visual feedback through LEDs.
- Simple push-button interface for user input.
- Customizable gameplay settings.

## Requirements

- Arduino Uno (or compatible board)
- 4 LEDs (different colors recommended)
- 4 Push Buttons
- Resistors (appropriate values for LEDs and buttons)
- Breadboard and connecting wires

## Circuit Diagram

The basic circuit setup includes connecting the LEDs to specific digital pins on the Arduino, each with a series resistor. The push buttons are connected to other digital pins, with one side going to ground.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/dan1471/Arduino-Memory-Game.git
    cd arduino-memory-game
    ```

2. Open the project in the Arduino IDE.

3. Verify and upload the code to your Arduino board:
    - Connect your Arduino to your computer via USB.
    - In the Arduino IDE, select your board and port.
    - Click on the **Upload** button.

## How to Play

1. **Power On**: Once the Arduino is powered on, the game will initialize, and the first LED in the sequence will flash.

2. **Replicate the Sequence**: After the LED flashes, press the corresponding button for that LED. If correct, the sequence will grow by one, and the game will continue.

3. **Game Over**: If you press the wrong button, the game will end, and the LEDs will flash rapidly. Reset the Arduino to start a new game.

4. **Increasing Difficulty**: With each successful replication, the sequence gets longer, making it more challenging.

## Customization

- You can modify the speed of the LED flashes and button response time by adjusting the delay values in the code.
- Change the pin assignments if you're using different pins or adding more LEDs and buttons.

## Troubleshooting

- **LEDs not lighting up?** Double-check your wiring and ensure the correct pins are used in the code.
- **Buttons not responding?** Ensure that your buttons are correctly connected with pull-down or pull-up resistors as needed.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
