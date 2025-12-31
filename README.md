# 🎮 Tetris Game

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A multiplayer Tetris game developed in C++ with support for various game modes, colors, and scoring system.

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

---

<div align="center"> <table> <tr> <td align="center" width="50%"> <h4>🤖 Computer vs Computer</h4> <video src="https://github.com/user-attachments/assets/a21dcc22-b144-4ce7-a775-cc507d85bc62" controls style="width:100%; max-width:420px; border-radius:14px; box-shadow:0 8px 24px rgba(0,0,0,0.25);"> </video> </td> <td align="center" width="50%"> <h4>👥 Human vs Computer</h4> <video src="https://github.com/user-attachments/assets/1201b93c-97d1-4551-84a2-a76b40917b98" controls style="width:100%; max-width:420px; border-radius:14px; box-shadow:0 8px 24px rgba(0,0,0,0.25);"> </video> </td> </tr> </table> </div>



**Enjoy the game! 🎮**
