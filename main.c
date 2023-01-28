#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_HEIGHT 25
#define BOARD_WIDTH 80
#define BOARD_X_MIDDLE 40

#define RACKET_UPPER_POSITION 7
#define RACKET_BOTTOM_POSITION 10
#define X_LEFT_RACKET 1
#define X_RIGHT_RACKET 79

#define SCORE_WIN 21

#define MOVE_UP 1
#define MOVE_MIDDLE_LEFT 2
#define MOVE_MIDDLE_RIGHT 3
#define MOVE_DOWN 4

char board[BOARD_HEIGHT][BOARD_WIDTH];
int ballInitX = 30;
int ballInitY;
int xBall;
int yBall;
int player1 = 0;
int player2 = 0;


void initBoard();

void initRackets();

void initBall();

void initGame();

void printBoard();

void ballInitMoving();

void move_racket();

int main() {
 //   initGame();

    initBoard();
    initRackets();
    printBoard();
    move_racket();
    printBoard();

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

int generateRandBallY();

void initBall() {
    ballInitY = generateRandBallY();
    board[ballInitY][ballInitX] = '*';
}

int generateRandBallY() {
    srand(time(NULL));
    return rand() % (BOARD_HEIGHT + 1);
}

void printBoard() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("%d : %d\n", player1, player1);
}

int ballMoveLeft() {
    char temp_char_l;
    int temp_pos_x_l = xBall - 1;
    if (temp_pos_x_l == 0) return 0;
    else {
        temp_char_l = board[yBall][temp_pos_x_l];
        board[yBall][temp_pos_x_l] = '*';
        board[yBall][xBall] = temp_char_l;
        xBall = temp_pos_x_l;
    }
    return 1;
}

void ballInitMoving() {
    xBall = ballInitX;
    yBall = ballInitY;
    while (xBall > 0 && xBall < BOARD_WIDTH &&
           yBall > 0 && yBall < BOARD_HEIGHT) {
        if (!ballMoveLeft()) {
            printf("\nFail\n");
            break;
        }
        printBoard();
    }
}

void move_racket() {
    char move;
    int upper_left = RACKET_UPPER_POSITION;
    int upper_right = RACKET_UPPER_POSITION;
    int bottom_left = RACKET_BOTTOM_POSITION;
    int bottom_right = RACKET_BOTTOM_POSITION;

    switch (move = getchar()) {
        case 'A':
            if (upper_left - 1 > 0) {
                board[bottom_left - 1][1] = ' ';
                board[upper_left - 1][1] = '\\';
            }
                break;
        case 'Z':
            if (bottom_left + 1 < BOARD_HEIGHT) {
                board[upper_left][1] = ' ';
                board[bottom_left][1] = '\\';
            }
            break;
        case 'K':
            if (upper_right - 1 > 0) {
                board[bottom_right - 1][BOARD_HEIGHT - 1] = ' ';
                board[upper_right - 1][BOARD_HEIGHT - 1] = '\\';
            }
            break;
        case 'M':
            if (bottom_right + 1 < BOARD_HEIGHT) {
                board[upper_right][BOARD_WIDTH - 1] = ' ';
                board[bottom_right][BOARD_WIDTH - 1] = '\\';
            }
                break;
    }
}

void score(int player) {
    if(player == 1) {
        player1++;
        if (player1 == SCORE_WIN) {
            printf("PLAYER 1 win!");
        }
        initGame();
    }
    if (player == 2) {
        player2++;
        if (player2 == SCORE_WIN) {
            printf("PLAYER 2 win!");
        }
        initGame();
    }
}

