# Minesweeper-Game
The details of this project - as far as what features the game should contain - were provided by the University of Florida, along with all the image textures used.

## A fully functional Minesweeper game created using C++ and the SFML library.
---
### What it looks like
![Demo](minesweeper demo.mp4)

### This game has three states

- Game Play State: the player is free to interact with all the tiles on the board
- Winner Game State: all mines are automatically flagged and the player must click the happy face with glasses to reset the board
- Loser Game State: all mines on the board are revealed and the player must click the sad happy face to reset the board

### Features

- Tiles are revealed when left-clicked and are assigned a number that corresponds to the number of mines adjacent to this tile.
- Mines are randomly placed in tiles across the board - depending on the mine counter - and if left-clicked, the player loses and is sent to the loser game state.
- Mine counter (bottom-left of screen) indicating the number of mines on the board, which changes depending on the number of flags placed.
- Unrevealed tiles are flagged and unflagged when right-clicked, which updates the mine counter, respectively.
- Tiles with no adjacent mines do not have a number assigned to them.
- If a tile is revealed and it has zero mines adjacent to it, all neighboring tiles with zero adjacent mines will also be automatically revealed, along with the corresponding neightbors of those revealed tiles.
- Button with a yellow face that resets the board when left-clicked and changes depending on the state of the game.
- Button with a mine and an eye that reveals and unreveals all the mines on the board when left-clicked.
- Three buttons for testing, each creating a unique board based on the config file assigned to it, which can be modified freely.

### Build instructions

- Clone and run on a C++ compiler.
- 
