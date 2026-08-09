#include <stdio.h>
#include <unistd.h>

#define GRID_ROWS 30
#define GRID_COLS 30
#define GRID (GRID_COLS*GRID_ROWS)
#define DEAD '.'
#define ALIVE '#'

/* returns the position transformed from bi-dimensional coordinates (x,y) to monodimensional y*GRID_COLS+y, managing the wrap-around */
int compute_position(int x, int y){
    if(x < 0){
        x = (-x) % GRID_ROWS;
        x = GRID_ROWS - x;
    }
    if(y < 0){
        y = (-y) % GRID_COLS;
        y = GRID_COLS - y;
    }
    if(x > 0) x = x % GRID_ROWS;
    if(y > 0) y = y % GRID_COLS;

    return x * GRID_COLS + y;
}


/* fills all the cells of the grid with a given state */
void fill_grid(char *grid, char state){
    for(int x = 0; x < GRID_ROWS; x++){
        for(int y = 0; y < GRID_COLS; y++){
            grid[compute_position(x, y)] = state;
        }
    }
}

/* prints the full grid, converting from the mono-dimensional grid to the bidimensional (x,y) grid for display. Also cleans the screen */
void print_grid(char *grid){
    printf("\x1b\x5b\x33\x4a\x1b\x5b\x48\x1b\x5b\x32\x4a"); /* clear | hexdump -C */
    for(int x = 0; x < GRID_ROWS; x++){
        for(int y = 0; y < GRID_COLS; y++){
            printf("%c", grid[compute_position(x,y)]);
        }
        printf("\n");
    }
}

/* sets a given cell (x,y) to a given state */
void set_cell(char *grid, int x, int y, char state){
    grid[compute_position(x,y)] = state;
}

char get_cell(char *grid, int x, int y){
    char state = grid[compute_position(x,y)];
    return state;
}


/* given a cell, checks if the 8 neighbours are dead or alive*/
int count_alive_neighbours(char *grid, int x, int y){
    int alive = 0;
    for(int xo = -1; xo <= 1; xo++){
        for(int yo = -1; yo <= 1; yo++){
            if(xo == 0 && yo == 0) continue;
            if(get_cell(grid, x+xo, y+yo) == ALIVE) alive++;
        }
        printf("\n");
    }
    return alive;
}

/* main function of the game, computes the next state from the old state */
void compute_next(char *old, char *new){
    int alive;
    for(int x = 0; x < GRID_ROWS; x++){
        for(int y = 0; y < GRID_COLS; y++){
            alive = count_alive_neighbours(old, x, y);
            char state = DEAD;
            if(get_cell(old, x, y) == ALIVE){
                if(alive == 2 || alive == 3){
                    state = ALIVE;
                }
            } else {
                if(alive == 3){
                    state = ALIVE;
                }
            }
            new[compute_position(x,y)] = state;
        }
    }
}



int main(void){
    char old_grid[GRID];
    char new_grid[GRID];

    fill_grid(old_grid, DEAD);
    
    /* glider */
    set_cell(old_grid, 10, 10, ALIVE);
    set_cell(old_grid, 10, 11, ALIVE);
    set_cell(old_grid, 10, 12, ALIVE);
    set_cell(old_grid, 9, 12, ALIVE);
    set_cell(old_grid, 8, 11, ALIVE);

    while(1){
        compute_next(old_grid, new_grid);
        print_grid(new_grid);
        usleep(100000);
        compute_next(new_grid, old_grid);
        print_grid(old_grid);
        usleep(100000);
    }

    return 0;
}