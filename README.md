# 🎮 Tetris Game

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A multiplayer Tetris game developed in C++ with support for various game modes, colors, and scoring system.

## 👥 Developers

- **Noy Zion** - 212198766
- **Dana Reshef** - 314652439

## ✨ Features

### Game Modes
- 🎯 **Human vs Human** - Two human players compete against each other
- 🤖 **Human vs Computer** - Human player vs AI opponent
- 🖥️ **Computer vs Computer** - Two AI players compete

### Bonus Features
- 🎨 **Colors** - Colorful game mode support
- 📊 **Scoring** - Advanced scoring system
- ⏸️ **Pause** - Ability to pause the game

## 🎮 How to Play

### Left Player Controls
- `A` / `a` - Move left
- `D` / `d` - Move right
- `S` / `s` - Rotate clockwise
- `W` / `w` - Rotate counter-clockwise
- `X` / `x` - Hard drop

### Right Player Controls
- `J` / `j` - Move left
- `L` / `l` - Move right
- `K` / `k` - Rotate clockwise
- `I` / `i` - Rotate counter-clockwise
- `M` / `m` - Hard drop

### General Controls
- `ESC` - Exit game
- `4` - Continue game (if paused)
- `8` - Instructions
- `9` - End game

## 📋 System Requirements

- **Operating System**: Windows 10 or higher
- **Compiler**: Visual Studio 2019 or higher (or any compatible C++ compiler)
- **Libraries**: Windows API (included with Windows)

## 🚀 Installation and Running

### Method 1: Visual Studio (Recommended)

1. Open the `TetrisGame_Noy_Dana.sln` file in Visual Studio
2. Select the build configuration (Debug or Release)
3. Press `F5` or select `Debug > Start Debugging`
4. The game will start automatically

### Method 2: Command Line Compilation

```bash
# Navigate to project directory
cd TetrisGame_Noy_Dana

# Compile with MSVC
cl /EHsc *.cpp /Fe:TetrisGame.exe

# Run
TetrisGame.exe
```

### Method 3: MinGW (if installed)

```bash
cd TetrisGame_Noy_Dana
g++ -o TetrisGame.exe *.cpp -static-libgcc -static-libstdc++
./TetrisGame.exe
```

## 📁 Project Structure

```
Tetris/
├── README.md                          # This file
├── readme.txt                         # Original README file
├── TetrisGame_Noy_Dana.sln           # Visual Studio solution file
└── TetrisGame_Noy_Dana/              # Main source code directory
    ├── main.cpp                       # Program entry point
    ├── menu.h / menu.cpp              # Menu system
    ├── tetrisGame.h / tetrisGame.cpp  # Main game logic
    ├── tetrisGameHuVSHu.cpp          # Human vs Human mode
    ├── player.h / player.cpp          # Base player class
    ├── human.h / human.cpp            # Human player
    ├── computer.h / computer.cpp      # Computer player
    ├── board.h / board.cpp            # Game board
    ├── shapes.h / shapes.cpp          # Tetris shapes
    ├── point.h / point.cpp            # Point representation
    ├── general.h / general.cpp        # General utilities
    ├── gameDef.h                      # Game definitions
    └── TetrisGame_Noy_Dana.vcxproj   # Visual Studio project file
```

## 🏗️ Architecture

The project is built in a modular way with clear separation between components:

- **Menu** - Menu management and game mode selection
- **TetrisGame** - Main game logic
- **Player** - Abstract base class for players
- **Human** - Human player implementation
- **Computer** - Computer player implementation with AI
- **Board** - Game board management
- **Shapes** - Tetris shapes management
- **Point** - Point representation in space

## 🎯 Game Rules

1. **Objective**: Prevent the board from filling up by arranging complete rows
2. **Scoring**: Points are awarded for each completed row
3. **Victory**: The first player to lose (board fills up) loses the game
4. **Shapes**: The game includes all 7 classic Tetris shapes (J, O, T, I, S, Z, L) + BOMB

## 🔧 Game Settings

Game settings are located in the `gameDef.h` file:

- **Board Size**: 12x18
- **Speed**: 200ms (configurable)
- **Board Positions**: Defined by MIN_X_LEFT, MIN_X_RIGHT, MIN_Y

## 🐛 Troubleshooting

### Issue: Program won't compile
**Solution**: Make sure you have Visual Studio installed with C++ support

### Issue: Program won't run
**Solution**: Ensure you're running from the correct directory and all files exist

### Issue: Controls don't work
**Solution**: Make sure the console window is active and focused

## 📝 License

This project was developed as part of an academic exercise.

## 🤝 Contributing

This project was developed by Noy Zion and Dana Reshef as part of an academic exercise.

## 📧 Contact

For questions or comments, please create an issue in this repository.

---

**Enjoy the game! 🎮**
