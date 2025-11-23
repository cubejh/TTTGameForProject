#include <stdio.h>

    /***
     1. add include "TTTgameCore.h"
     2. use init_state() and push_button(n) (maybe getGameState()), other would do automatically
     ***/


typedef struct {
    /***
        board: 0 is O, 1 is X, -1 is non-fill
        0,1,2
        3,4,5
        6,7,8
        curplayer: 0 is O, 1 is X (who lead board change this time)
        detwinner: 0 no winner, 1 has winner
        success: the move legal or not
    ***/
    int board[9];
    int curplayer;
    int detwinner;
    int success;
} game_state;

int PQ[2][3];//playerQueue
int pt[2];
game_state gameState;


void printBoard(){ // can be used as a reference and modified as needed
    if(!gameState.success){
        printf("illeagal move!!!\n");
        return;
    }
    for(int i=0;i<9;i++){
        (!gameState.board[i])?printf("O"):(gameState.board[i]==1)?printf("X"):printf("-");
        if(i%3==2)
            printf("\n");
    }
    if(gameState.detwinner){
        (gameState.curplayer)?printf("X win the game\n"):printf("O win the game\n");
        printf("by %d,%d,%d", PQ[gameState.curplayer][0], PQ[gameState.curplayer][1], PQ[gameState.curplayer][2]);
    }
    else
        (gameState.curplayer)?printf("O's turn\n"):printf("X's turn\n");
    printf("************\n");
}

int detwinner(int i){
    if(PQ[i][2]==-1)
        return 0;
    if(PQ[i][0]%3==PQ[i][1]%3 && PQ[i][1]%3==PQ[i][2]%3) // same column
        return 1;
    if(PQ[i][0]/3==PQ[i][1]/3 && PQ[i][1]/3==PQ[i][2]/3) // same row
        return 1;
    if(PQ[i][1]==4 && PQ[i][0]+PQ[i][1]+PQ[i][2]==12)// dia
        return 1;
    return 0; 
}

void init_state(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            PQ[i][j]=-1;
    for(int i=0;i<9;i++)
        gameState.board[i]=-1;
    pt[0]=0;
    pt[1]=0;
    gameState.curplayer = 0;
    gameState.detwinner = 0;
    gameState.success = 1;
    //printBoard(); who turns need diff logic, only for check board;
}

void pushButton(int num){
    printf("try put the piece to %d...\n", num);

    if(gameState.board[num] > -1){
        gameState.success=0;
        printBoard();
        return;
    }
    gameState.success = 1;
    gameState.board[num] = gameState.curplayer;
    if(PQ[gameState.curplayer][pt[gameState.curplayer]] > -1)
        gameState.board[PQ[gameState.curplayer][pt[gameState.curplayer]]] = -1;
    PQ[gameState.curplayer][pt[gameState.curplayer]] = num;
    pt[gameState.curplayer] = (pt[gameState.curplayer]+1) % 3;
    gameState.detwinner = detwinner(gameState.curplayer);
    printBoard();
    gameState.curplayer = (gameState.curplayer + 1) % 2;
}

game_state getGameState(){
    return gameState;
}

/*
void mocking_state(){
    int mockingBoard[] = {-1,0,-1,-1,-1,1,-1,-1,-1};
    int mocking_curplayer = 0;
    int mocking_detwinner = 0;
    for(int i=0;i<9;i++)
        gameState.board[i] = mockingBoard[i];
    gameState.curplayer = mocking_curplayer;
    gameState.detwinner = mocking_detwinner;
}
*/

/*
int main(){
    init_state();
    int a[] = {1,5,2,0,5,3,7,6,1,4,8,2};
    for(int i=0;i<15;i++){
        pushButton(a[i]);
        if(gameState.detwinner)
            return 0;
    }     
    return 0;
}
*/