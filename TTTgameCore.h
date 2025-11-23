#ifndef GAME_H
#define GAME_H

typedef struct {
    int board[9];
    int curplayer;
    int detwinner;
    int success;
} game_state;

extern game_state gameState;

void init_state(void);
void pushButton(int num);
void printBoard(void);
int detwinner(int i);
void mocking_state(void);
game_state getGameState(void);

#endif
