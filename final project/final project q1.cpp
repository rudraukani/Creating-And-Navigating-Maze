#include <stdio.h>
#include <stdbool.h>

#define MAZE_SIZE 12

void printMaze(char maze[MAZE_SIZE][MAZE_SIZE]);
bool mazeTraverse(char maze[MAZE_SIZE][MAZE_SIZE], int x, int y, int direction);

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE] = {
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
         {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
         {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
         {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.'},
         {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
         {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
         {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
         {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
         {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
         {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    if (!mazeTraverse(maze, 2, 0, 0)) {
        printf("No exit found.\n");
    }

    return 0;
}

void printMaze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isWall(char maze[MAZE_SIZE][MAZE_SIZE], int x, int y) {
    return x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE || maze[x][y] == '#';
}

bool mazeTraverse(char maze[MAZE_SIZE][MAZE_SIZE], int x, int y, int direction) {
    // scenario of exit
    if (x == MAZE_SIZE - 1 && y >= 0 && y < MAZE_SIZE && maze[x][y] == 'X') {
        printMaze(maze);
        printf("Exit found!\n");
        return true;
    }

    // symbol for path
    if (maze[x][y] == '.' || maze[x][y] == 'S') {
        maze[x][y] = 'X';
        printMaze(maze);
    }

    // Check for the right-hand side wall based on the current direction
    int rightX = x, rightY = y;
    switch (direction) {
    case 0: //  right
        rightX++;
        break;
    case 1: //  down
        rightY--;
        break;
    case 2: //  left
        rightX--;
        break;
    case 3: //  up
        rightY++;
        break;
    }

    // Turn right 
    if (!isWall(maze, rightX, rightY)) {
        return mazeTraverse(maze, rightX, rightY, (direction + 1) % 4);
    }

    // Move forward if right has no way
    int forwardX = x, forwardY = y;
    switch (direction) {
    case 0: //  right
        forwardY++;
        break;
    case 1: //  down
        forwardX++;
        break;
    case 2: //  left
        forwardY--;
        break;
    case 3: //  up
        forwardX--;
        break;
    }

    if (!isWall(maze, forwardX, forwardY)) {
        return mazeTraverse(maze, forwardX, forwardY, direction);
    }

    // Turn left if forward has no way
    return mazeTraverse(maze, x, y, (direction + 3) % 4);
}

