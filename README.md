# Game Of Life
This is a simple interpretation of Conway's Game of Life, a cellar automation devised by the mathemathician John Horton Conway.

## Rules
This game has very simple rules. It consists of a grid of cells (sometimes infinite, sometimes with a wrap-around mechanic) that can be either alive or dead.
Every cell has 8 neighbours:

NW N NE

W  .  E 

SW S SE

If a cell is alive and has 2 or 3 living neighbours, it remains alive; otherwise, it dies (<2 due to underpopulation, >3 due to overpopulation).
If a cell is dead and has exactly 3 living neighbours, it becomes alive in the next generation; otherwise, it remains dead.

## Implementation
The player will choose the positions of the initial live cells in the main function/file, by providing the x and y coordinates for each cell. The game will play by itself once it starts.

## Logic
The grid will use a wrap-around mechanic: the grid edges connect so that the last cell on the x-axis neighbours the first cell on that same axis. The same rule applies to the y-axis.
