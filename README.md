# Biriyani Hunter 🍛

A thrilling console-based shooting game where you defend your precious Biriyani from waves of enemies across three challenging levels!

## Game Overview

**Biriyani Hunter** is an action-packed 2D shooter game built entirely in C++ for Windows console. Navigate through obstacles, dodge enemy fire, and eliminate all threats to protect your Biriyani. Features include smooth animations, multiple enemy types, progressive difficulty levels, and a save/load system to resume your progress.

## Features

### Gameplay Mechanics
- **Three Progressive Levels**: Each level introduces new enemies and increased difficulty
- **Multiple Enemy Types**: Face up to 3 different enemies simultaneously in level 3
- **Health System**: Start with 100 health, collect health pills (+10 HP) to survive longer
- **Scoring System**: Earn 10 points for each enemy hit
- **Obstacle Navigation**: Strategically positioned barriers provide cover and challenge
- **Save & Resume**: Save your progress mid-game and resume later

### Combat System
- **Player Shooting**: Fire bullets upward with spacebar
- **Enemy Shooting**: Enemies fire downward with random patterns
- **Collision Detection**: Sophisticated hitbox system for bullets, enemies, and obstacles
- **Enemy Health**: Each enemy requires 5 hits to defeat
- **Damage Values**:
  - Enemy bullet hit: -20 HP
  - Enemy collision: -40 HP
  - Health pill pickup: +10 HP (max 100)

### Level Progression
1. **Level 1**: Single enemy with horizontal movement
2. **Level 2**: Two enemies with complex movement patterns
3. **Level 3**: Three enemies with varied attack strategies
4. **Victory**: Defeat all enemies in Level 3 to win!

## Controls

| Key | Action |
|-----|--------|
| **Arrow Keys** | Move player (Up/Down/Left/Right) |
| **Space Bar** | Fire weapon |
| **ESC** | Pause game (Resume or Exit) |

## Technical Requirements

### System Requirements
- **OS**: Windows (7, 8, 10, 11)
- **Compiler**: C++ Compiler with C++11 support or later
- **Console**: Windows Command Prompt or PowerShell

### Required Libraries
```cpp
#include <iostream>      // Input/output
#include <windows.h>     // Console manipulation
#include <conio.h>       // Keyboard input
#include <climits>       // Integer limits
#include <random>        // Random number generation
#include <chrono>        // Time-based operations
#include <fstream>       // File handling
#include <sstream>       // String stream
#include <string>        // String operations
```

## Installation & Setup

1. **Download/Clone the Source Code**
   ```bash
   git clone <repository-url>
   cd biriyani-hunter
   ```

2. **Compile the Game**
   ```bash
   g++ biriyani_hunter.cpp -o biriyani_hunter.exe
   ```

3. **Run the Game**
   ```bash
   biriyani_hunter.exe
   ```

## How to Play

### Starting the Game
1. Launch the executable
2. Choose between:
   - **1. New Game**: Start fresh
   - **2. Resume Game**: Continue from last save
3. Read the instructions screen
4. Press any key to begin

### Gameplay Tips
- **Stay Mobile**: Keep moving to avoid enemy bullets
- **Use Cover**: Hide behind obstacles when overwhelmed
- **Collect Pills**: Health pills spawn at critical moments (10 HP and 40 HP thresholds)
- **Target Priority**: Focus on enemies with predictable patterns first
- **Conserve Health**: Each life matters - avoid direct enemy contact
- **Save Often**: Game auto-saves on hits and level progression

### Winning Strategy
1. Master movement patterns of each enemy type
2. Learn obstacle positions for quick escapes
3. Time your shots to maximize hits
4. Collect health pills immediately when they appear
5. Use the pause feature to plan your next move

## Game Mechanics Deep Dive

### Player Character
- **Appearance**: ASCII art soldier (`O`, `/|\==`, `/ \`)
- **Starting Position**: Bottom-left corner
- **Movement**: Can move in all four directions within boundaries
- **Weapon**: Upward-firing projectile (represented by `|`)

### Enemies
- **Visual**: ASCII art enemies (`+`, `/|\==`, `/ \`)
- **Colors**: Blue (enemies), Red (obstacles), Green (player), Yellow (bullets)
- **Movement Patterns**:
  - **Enemy 1**: Horizontal sweep across screen
  - **Enemy 2**: Complex diagonal and vertical patterns
  - **Enemy 3**: Obstacle-aware navigation
- **Firing**: Random downward shots (represented by `!`)

### Obstacles
- **Symbol**: `#` characters
- **Color**: Red
- **Function**: Block both player and enemy bullets
- **Layout**: Strategic placement creates cover points and challenges

### Health Pills
- **Symbol**: `+`
- **Color**: Green
- **Spawn Condition**: Appears when health drops to 40 or 10
- **Effect**: Restores 10 HP
- **Behavior**: Falls from top of screen, disappears on collision or reaching bottom

## Data Persistence

### Save File
- **Filename**: `biriyani_hunter_save.txt`
- **Format**: CSV with headers
- **Auto-Save Events**:
  - Enemy hit
  - Player hit
  - Level progression
  - Game pause

### Saved Data Includes
- Player position (X, Y)
- Score and level
- Health status
- All enemy positions and health
- Enemy movement states
- Level progression flags

## Architecture

### Key Functions

**Movement & Control**
- `move()` - Main game loop and player control
- `move_enemy()` - Manages all enemy movements
- `moveEnemy1/2/3()` - Individual enemy movement patterns

**Combat System**
- `playerFire()` - Initialize player bullet
- `enemyFire()` - Random enemy firing
- `movePlayerBullets()` - Bullet physics and collision
- `moveEnemyBullets()` - Enemy projectile handling

**Game State**
- `printMaze()` - Draw game boundaries and HUD
- `printObstacles()` - Render level obstacles
- `pauseMenu()` - Pause screen with options
- `Gameover()` - Display defeat screen
- `win()` - Display victory screen

**Utilities**
- `gotoxy()` - Console cursor positioning
- `setcolor()` - Console text coloring
- `hideCursor()` / `showCursor()` - Cursor visibility
- `checkObstacles()` - Collision detection
- `random()` - Random number generation

**File Operations**
- `saveGameDataWithHeaders()` - Save game state
- `loadGameData()` - Load saved game
- `resumeGame()` - Resume menu

### Color Scheme
- **02** (Green): Player character
- **01** (Blue): Enemy characters
- **04** (Red): Obstacles and game over screen
- **06** (Yellow): Game borders and headers
- **0A** (Light Green): Victory screen
- **0E** (Yellow): Pause menu
- **09** (Light Blue): Menu options

## Scoring & Progression

### Score Calculation
- Base: 10 points per enemy hit
- No penalty for misses or damage taken
- Score persists through save/load

### Level Advancement
- **Level 1 → 2**: Defeat Enemy 1 (50 points minimum)
- **Level 2 → 3**: Defeat Enemies 1 & 2 (100 points minimum)
- **Victory**: Defeat all 3 enemies (150 points minimum)

## Known Features

### Performance Optimizations
- Bullet array management (max 100 per side)
- Timed enemy movements (150ms delay)
- Fire rate limiting (120ms cooldown)
- Region save/restore for pause menu

### Visual Effects
- UTF-8 encoded ASCII art for title screens
- Color-coded elements for clarity
- Smooth movement animations
- Screen flash on hits (`\a` sound alert)

## Troubleshooting

### Common Issues

**Game doesn't start**
- Ensure you're running on Windows
- Check compiler supports C++11 or later
- Verify console window is maximized

**Controls not responding**
- Click on the console window to focus it
- Check if another program is intercepting key presses

**Graphics look distorted**
- Maximize console window
- Use default console font (Raster or Consolas)
- Ensure console encoding is UTF-8

**Save file not loading**
- Check if `biriyani_hunter_save.txt` exists in game directory
- Ensure file isn't corrupted or manually edited
- Try starting a new game first

### Performance Tips
- Close unnecessary background programs
- Use Windows Command Prompt (better performance than PowerShell)
- Ensure console buffer size matches window size

## Future Enhancement Ideas
- Multiple difficulty modes
- Power-ups (rapid fire, shields, etc.)
- Additional enemy types
- Boss battles
- High score leaderboard
- Sound effects and music
- Customizable controls
- Achievement system

## Credits

**Game Design & Development**: Original concept and implementation  
**Engine**: Custom C++ console game engine  
**Platform**: Windows Console API

## License

This project is open-source and available for educational purposes. Feel free to modify and enhance the game!

## Contributing

Contributions are welcome! Some ideas:
- Add new enemy types
- Create additional levels
- Implement power-up system
- Add sound effects
- Create difficulty settings
- Improve AI patterns

## Version History

**Version 1.0** (Current)
- Three complete levels
- Save/load system
- Health pill mechanic
- Multiple enemy types
- Obstacle navigation
- Pause functionality

---

**Enjoy your Biriyani hunting adventure!** 🍛🎮

*"Kill the enemies and save the Biriyani!"*