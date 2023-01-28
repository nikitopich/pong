#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_HEIGHT 16
#define BOARD_WIDTH 61
#define BOARD_X_MIDDLE 30

#define RACKET_UPPER_POSITION 6
#define RACKET_BOTTOM_POSITION 10
#define X_LEFT_RACKET 1
#define X_RIGHT_RACKET 59

#define MOVE_UP_LEFT 0
#define MOVE_UP_RIGHT 1
#define MOVE_DOWN_LEFT 2
#define MOVE_DOWN_RIGHT 3

char board[BOARD_HEIGHT][BOARD_WIDTH];
int ballInitX = 30;
int ballInitY;
int xBall;
int yBall;

void initGame();

void initBoard();

void initRackets();

void initBall();

void printBoard();

void ballInitMoving();

int ballMoveLeft();

int ballMoveRight();

int generateRandBallY();

void switchHorizontalBallAndBoardProp(char temp_char, int temp_pos);

void switchVerticalBallAndBoardProp(char temp_char, int temp_pos);

int moveBallHorizontal(int temp_pos, int deadLine);

int ballMoveUp();

int ballMoveDown();

int moveBallVertical(int temp_pos, int deadLine);

int main() {
    initGame();
    ballInitMoving();

    return 0;
}

void initGame() {
    initBoard();
    initRackets();
    initBall();
}

void initBoard() {
    int j;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (j = 0; j < BOARD_X_MIDDLE; ++j) {
            board[i][j] = ' ';
        }
//        printf("j= %d, i= %d\n", j, i);
        board[i][j] = '|';
        for (j = j + 1; j < BOARD_WIDTH; ++j) {
            board[i][j] = ' ';
        }
    }
}

void initRackets() {
    for (int i = RACKET_UPPER_POSITION; i < RACKET_BOTTOM_POSITION; ++i) {
        board[i][X_LEFT_RACKET] = '\\';
        board[i][X_RIGHT_RACKET] = '\\';
    }
}

void initBall() {
    ballInitY = generateRandBallY();
    board[ballInitY][ballInitX] = '*';
}

int generateRandBallY() {
    srand(time(NULL));
    return rand() % (BOARD_HEIGHT + 1);
}

void ballInitMoving() {
    xBall = ballInitX;
    yBall = ballInitY;
    srand(time(NULL));
    int direction = rand() % (4 + 1);
    while (xBall > 0 && xBall < BOARD_WIDTH &&
           yBall > 0 && yBall < BOARD_HEIGHT)
    {
        switch (direction) {
            case MOVE_UP_LEFT: {
                switch (ballMoveLeft()) {
                    case 0: {
                        return;
                    }
                    case -1: {
                        direction = MOVE_UP_RIGHT;
                        break;
                    }
                }
                if (!ballMoveUp()) {
                    direction = MOVE_DOWN_LEFT;
                }
                break;
            }
            case MOVE_DOWN_LEFT: {
                switch (ballMoveLeft()) {
                    case 0: {
                        return;
                    }
                    case -1: {
                        direction = MOVE_DOWN_RIGHT;
                        break;
                    }
                }
                if (!ballMoveDown()) {
                    direction = MOVE_UP_LEFT;
                }
                break;
            }
            case MOVE_UP_RIGHT: {
                switch (ballMoveRight()) {
                    case 0: {
                        return;
                    }
                    case -1: {
                        direction = MOVE_UP_LEFT;
                        break;
                    }
                }
                if (!ballMoveUp()) {
                    direction = MOVE_DOWN_RIGHT;
                }
                break;
            }
            case MOVE_DOWN_RIGHT: {
                switch (ballMoveRight()) {
                    case 0: {
                        return;
                    }
                    case -1: {
                        direction = MOVE_DOWN_LEFT;
                        break;
                    }
                }
                if (!ballMoveDown()) {
                    direction = MOVE_UP_RIGHT;
                }
                break;
            }

        }
    }
}

int ballMoveLeft() {
    int temp_pos_x_l = xBall - 1;
    return moveBallHorizontal(temp_pos_x_l, 0);
}

int ballMoveRight() {
    int temp_pos_x_r = xBall + 1;
    return moveBallHorizontal(temp_pos_x_r, BOARD_WIDTH);
}

int moveBallHorizontal(int temp_pos, int deadLine) {
    char temp_char = board[yBall][temp_pos];
    if (temp_char == '\\') return -1;
    if (temp_pos == deadLine) {
        printf("\nFail\n");
        return 0;
    }
    else {
        switchHorizontalBallAndBoardProp(temp_char, temp_pos);
    }
    return 1;
}

void switchHorizontalBallAndBoardProp(char temp_char, int temp_pos) {
    board[yBall][temp_pos] = '*';
    board[yBall][xBall] = temp_char;
    xBall = temp_pos;
}

int ballMoveUp() {
    int temp_pos_y_u = yBall - 1;
    return moveBallVertical(temp_pos_y_u, 0);
}

int ballMoveDown() {
    int temp_pos_y_d = yBall + 1;
    return moveBallVertical(temp_pos_y_d, BOARD_HEIGHT);
}

int moveBallVertical(int temp_pos, int deadLine) {
    char temp_char = board[temp_pos][xBall];
    if (temp_pos == deadLine) return 0;
    else {
        switchVerticalBallAndBoardProp(temp_char, temp_pos);
    }
    return 1;
}

void switchVerticalBallAndBoardProp(char temp_char, int temp_pos) {
    board[temp_pos][xBall] = '*';
    board[yBall][xBall] = temp_char;
    yBall = temp_pos;
}

void printBoard() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    if (board[ballInitY][ballInitX])
        printf("\n");
}

void move_racket_up() {
    int who;

}

