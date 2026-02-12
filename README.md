# snake_game

## Description

A classic Snake game implementation in C for the terminal. Navigate the snake to eat food, grow longer, and achieve the highest score without hitting the walls or yourself.

## Controls

| Key                 | Action     |
| ------------------- | ---------- |
| `W` / `Up Arrow`    | Move Up    |
| `S` / `Down Arrow`  | Move Down  |
| `A` / `Left Arrow`  | Move Left  |
| `D` / `Right Arrow` | Move Right |
| `Q`                 | Quit Game  |

## Requirements

- GCC compiler
- Linux environment (for pthread and terminal handling)

## Project Structure

- `main.c`: Entry point. Initializes the playground, starts the key handler thread, and runs the render loop.
- `playground.c`: Manages the game grid, updates game state (snake movement, eating food), and renders the frame.
- `snake.c`: Snake logic. Initializes the snake, handles growth, and manages movement direction.
- `keys_handler.c`: Runs in a separate thread to capture user input asynchronously without blocking the render loop.
- `terminal.c`: Handles terminal configuration (raw mode) to read individual keystrokes.
- `points.c`: Utility functions for managing the doubly linked list structure used for the snake body.
- `main.h`: Header file containing structs, enums, constants, and function prototypes.

## Technical Implementation

### Data Structures

- **Snake**: Implemented as a doubly linked list (`pointnode_t`). The `head` represents the snake's head, and the `tail` is the end. Growing adds a new node to the tail.
- **Playground**: A 2D grid (`char grid[ROWS][COLUMNS]`) representing the game board.

### Concurrency

- **Multithreading**: The game uses `pthread` to run the input handler (`keys_handler`) in a separate thread. This allows the render loop to run at a fixed tick rate while still remaining responsive to user input.

### Rendering

- **Termios**: The terminal is switched to non-canonical mode (raw mode) to capture input immediately without pressing Enter.

- **Double Buffering Simulation**: To avoid flickering, `system("clear")` was replaced with ANSI escape codes (`\033[H`) to reset the cursor position and overwrite the screen buffer, providing a smoother visual experience.

## How to Run

### Compile

```bash
gcc *.c -o snake -lpthread -lm
```

### Run

```bash
./snake
```
