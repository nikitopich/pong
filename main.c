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

#define MOVE_UP 1
#define MOVE_MIDDLE_LEFT 2
#define MOVE_MIDDLE_RIGHT 3
#define MOVE_DOWN 4

char board[BOARD_HEIGHT][BOARD_WIDTH];
int ballInitX = 30;
int ballInitY;
int player1Win = 0;
int player2Win = 0; // 0/1
int xBall;
int yBall;

void initBoard();

void initRackets();

void initBall();

void initGame();

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
//    printBoard();

    return 0;
}

void initGame() {
    initBoard();
    initRackets();
    initBall();
    ballInitMoving();
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
    while (xBall > 0 && xBall < BOARD_WIDTH &&
           yBall > 0 && yBall < BOARD_HEIGHT) {
        if (!ballMoveLeft()) {
            printf("\nFail\n");
            player2Win = 1;
            break;
        }
        if (!ballMoveRight()) {
            printf("\nFail\n");
            player1Win = 1;
            break;
        }
        if (!ballMoveUp()) {
            break;
        }
        if (!ballMoveDown()) {
            printf("\nFail\n");
            player1Win = 1;
            break;
        }

        printBoard();
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
    if (temp_pos == deadLine) return 0;
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
    return moveBallVertical(temp_pos_y_u, BOARD_HEIGHT);
}

int ballMoveDown() {
    int temp_pos_y_d = yBall + 1;
    return moveBallVertical(temp_pos_y_d, 0);
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

