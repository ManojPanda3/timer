# Timer - Your Lightweight CLI Clock

---

![Timer Screenshot](./img/screenshot1.png)

_A quick glance at the Timer in action, counting away the seconds in your terminal._

## Overview

**Timer** is a minimalist and efficient command-line interface (CLI) program, meticulously crafted in C, designed to help you track time effortlessly. For those who prefer a focused, distraction-free environment, `timer` offers a straightforward solution: simply execute the command, and it begins counting time instantly, right in your terminal. It's built with simplicity and resourcefulness at its core, making it an ideal utility for developers, students, or anyone who needs a quick, no-fuss timer without the overhead.

## Key Features

- **Bare-Bones Simplicity:** Say goodbye to cluttered interfaces. `timer` offers a clean experience—just run the command, and it starts counting.
- **Resource Friendly:** Engineered in C, `timer` boasts an incredibly small footprint. It's designed to avoid dynamic memory allocation (meaning no `malloc` or `free` calls), ensuring maximum stability and minimal resource consumption.
- **Instant Utility:** Perfect for tracking quick focus sessions, monitoring elapsed time during tasks, or even as a persistent, unobtrusive clock in your terminal workflow.
- **Highly Portable:** While developed and primarily tested on Linux (specifically Arch Linux, as you prefer!), its pure C codebase allows for easy compilation and use across various Unix-like systems.

## How to Use

Using `timer` is as straightforward as it gets:

## Bash

## #timer

Once executed, the timer will begin counting from `00:00:00` and update every second, providing real-time tracking until you choose to terminate the program (typically by pressing `Ctrl+C`).

## Installation

Getting `timer` set up on your system is simple.

### Prerequisites

To build and install `timer`, you'll need:

- A C compiler (like `gcc`)
- The `make` utility
- `git` for cloning the repository

### Build and Install Steps

1. **Clone the repository:**
   Start by fetching the project files to your local machine.

   ```Bash
   git clone --depth 1 https://github.com/ManojPanda3/timer.git
   ```

2. **Navigate to the project directory:**

   ```Bash
   cd timer
   ```

3. **Compile the source code:**
   The provided `Makefile` will handle the compilation, producing the executable binary.

   ```Bash
   make
   ```

4. **Install the binary:**
   Copy the compiled `timer` executable to a directory that's included in your system's `$PATH` (e.g., `~/.local/bin/`). This makes the `timer` command available from any directory in your terminal.

   ```Bash
   sudo cp ./build/timer ~/.local/bin/
   ```

   _If `~/.local/bin/` isn't already in your `$PATH`, you might need to add it by including `export PATH="$HOME/.local/bin:$PATH"` in your shell's configuration file (e.g., `~/.bashrc`, `~/.zshrc`), followed by `source`ing that file._

5. **Run the timer:**
   After installation, you can open a new terminal or `source` your shell configuration, then simply type `timer` to start it!

   ```Bash
   timer
   ```

## Contributing

Timer is an open-source project, and your contributions are highly valued! If you have ideas for new features, bug fixes, or general improvements, please feel free to contribute:

1. Fork the repository.
2. Create a new branch for your feature or fix (`git checkout -b feature/your-awesome-feature`).
3. Make your changes.
4. Commit your changes with a clear message (`git commit -m 'Add a brief description of your changes'`).
5. Push your branch to your forked repository (`git push origin feature/your-awesome-feature`).
6. Open a Pull Request to the main repository.

## License

This project is open-source and released under the **MIT License**. For complete details, please refer to the `LICENSE` file in the repository.

## About the Author

**Timer** is developed by Manoj Kumar Panda. Explore more of my projects on [GitHub](https://github.com/manojpanda3) or connect with me professionally on [LinkedIn](https://www.linkedin.com/in/manoj-panda-3a79452b0/).

---
