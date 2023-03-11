#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 15
#define COLS 20

struct cell {
    int row, col;
    int walls[4]; // 0: top, 1: right, 2: bottom, 3: left
    int visited;
};

void initialize_maze(struct cell maze[][COLS]);
void print_maze(struct cell maze[][COLS]);
void generate_maze(struct cell maze[][COLS], int row, int col);
int get_random_neighbor(struct cell maze[][COLS], int row, int col);
void remove_wall(struct cell maze[][COLS], int row1, int col1, int row2, int col2);

int main(void) {
    struct cell maze[ROWS][COLS];

    srand(time(NULL));
    initialize_maze(maze);
    generate_maze(maze, 0, 0);
    print_maze(maze);

    return 0;
}

void initialize_maze(struct cell maze[][COLS]) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            maze[i][j].row = i;
            maze[i][j].col = j;
            maze[i][j].visited = 0;

            // initialize walls
            maze[i][j].walls[0] = 1;
            maze[i][j].walls[1] = 1;
            maze[i][j].walls[2] = 1;
            maze[i][j].walls[3] = 1;
        }
    }

    // remove top wall of starting cell
    maze[0][0].walls[0] = 0;

    // remove bottom wall of ending cell
    maze[ROWS - 1][COLS - 1].walls[2] = 0;
}

void print_maze(struct cell maze[][COLS]) {
    int i, j;

    // print top wall
    printf(" ");
    for (j = 0; j < COLS; j++) {
        printf("__");
    }
    printf("\n");

    for (i = 0; i < ROWS; i++) {
        // print left wall
        printf("|");

        for (j = 0; j < COLS; j++) {
            // print bottom wall if present
            if (maze[i][j].walls[2] == 1) {
                printf("_");
            } else {
                printf(" ");
            }

            // print right wall if present
            if (maze[i][j].walls[1] == 1) {
                printf("|");
            } else {
                printf(" ");
            }
        }

        printf("\n");
    }
}

void generate_maze(struct cell maze[][COLS], int row, int col) {
    int neighbor;

    maze[row][col].visited = 1;

    while ((neighbor = get_random_neighbor(maze, row, col)) != -1) {
        switch (neighbor) {
            case 0: // top
                remove_wall(maze, row, col, row - 1, col);
                generate_maze(maze, row - 1, col);
                break;
                        case 1: // right
                remove_wall(maze, row, col, row, col + 1);
                generate_maze(maze, row, col + 1);
                break;
            case 2: // bottom
                remove_wall(maze, row, col, row + 1, col);
                generate_maze(maze, row + 1, col);
                break;
            case 3: // left
                remove_wall(maze, row, col, row, col - 1);
                generate_maze(maze, row, col - 1);
                break;
        }
    }
}

int get_random_neighbor(struct cell maze[][COLS], int row, int col) {
    int neighbors[4];
    int count = 0;

    // check top neighbor
    if (row > 0 && maze[row - 1][col].visited == 0) {
        neighbors[count] = 0;
        count++;
    }

    // check right neighbor
    if (col < COLS - 1 && maze[row][col + 1].visited == 0) {
        neighbors[count] = 1;
        count++;
    }

    // check bottom neighbor
    if (row < ROWS - 1 && maze[row + 1][col].visited == 0) {
        neighbors[count] = 2;
        count++;
    }

    // check left neighbor
    if (col > 0 && maze[row][col - 1].visited == 0) {
        neighbors[count] = 3;
        count++;
    }

    if (count == 0) {
        return -1;
    } else {
        int index = rand() % count;
        return neighbors[index];
    }
}

void remove_wall(struct cell maze[][COLS], int row1, int col1, int row2, int col2) {
    // remove wall between two cells
    if (row1 == row2 && col1 < col2) {
        maze[row1][col1].walls[1] = 0;
        maze[row2][col2].walls[3] = 0;
    } else if (row1 == row2 && col1 > col2) {
        maze[row1][col1].walls[3] = 0;
        maze[row2][col2].walls[1] = 0;
    } else if (row1 < row2 && col1 == col2) {
        maze[row1][col1].walls[2] = 0;
        maze[row2][col2].walls[0] = 0;
    } else if (row1 > row2 && col1 == col2) {
        maze[row1][col1].walls[0] = 0;
        maze[row2][col2].walls[2] = 0;
    }
}

           
