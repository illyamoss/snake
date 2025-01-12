# Snake Game in Raylib 🎮

This is a simple implementation of the classic Snake game built using the [raylib](https://www.raylib.com/) C library. The game is lightweight, fun, and a great way to learn game development in C. 🐍

![Game Preview](https://github.com/illyamoss/snake/preview/game.jpg)
![Game Preview](https://github.com/illyamoss/snake/preview/win.jpg)

## 🎯 Objective

- **Win**: Achieve a score of **100** points by eating the food.
- **Lose**: The game ends if:
  - The snake collides with itself.
  - The snake goes out of bounds.

## 🚀 Features

- Smooth and responsive controls (WASD or Arrow Keys).
- Randomly placed food for the snake to eat.
- Score counter displayed on the screen.
- Victory and game-over conditions.
- Clean and minimalistic UI.

## 🛠️ How to Build and Run

### Prerequisites

- **raylib**: Ensure you have raylib installed. You can install it via [vcpkg](https://vcpkg.io/) with the following commands:
  ```bash
  vcpkg install raylib
  vcpkg integrate install
A C compiler (e.g., GCC).
Make sure to include your raylib installation path in the Makefile. Update the CFLAGS and LDFLAGS variables accordingly.
Build and Run
To compile and run the game:

Clone the repository:

bash
Copy code
git clone https://github.com/illyamoss/snake.git
cd snake
Build and run:

bash
Copy code
make && ./build/program
The Makefile is preconfigured for a raylib installation via vcpkg. Ensure your paths match your environment.

🕹️ Controls
W: Move Up
S: Move Down
A: Move Left
D: Move Right


📜 Code Highlights
Collision Detection: Ensures the snake doesn’t collide with itself or the screen boundaries.
Random Food Placement: The food appears at a random location on the screen.
Dynamic Growth: The snake grows longer each time it eats food.
🏆 Winning the Game
To win, simply reach a score of 100 by eating food. 🎉

📄 License
This project is licensed under the MIT License. Feel free to use, modify, and share!

Happy Coding! 🚀

markdown
Copy code

### Notes:
- Replace `https://github.com/your-username/snake-game-raylib.git` with the actual repository URL.
- Verify that the raylib installation path matches the one specified in your `Makefile`.
- Users can adjust the `Makefile` as needed for their specific setup.