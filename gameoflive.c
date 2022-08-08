#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define X_BOARD  100
#define Y_BOARD  300



void inicializeBoard(int board[X_BOARD][Y_BOARD]){
    for(int i=0;i<X_BOARD;i++){
        for(int j=0;j<Y_BOARD;j++){
            int randbool = rand() & 1;
            board[i][j] = randbool;
        }
    }
}

void printBoard(int board[X_BOARD][Y_BOARD]){
    for(int i=0;i<X_BOARD;i++){
        for(int j=0;j<Y_BOARD;j++){
           if(board[i][j]==1){
                printf("*");
           }else {
                printf("-");
           }
        }printf("\n");
    }
}

void checkCellNeighbours(int board[X_BOARD][Y_BOARD], int new_board[X_BOARD][Y_BOARD]){
    for(int i=0;i<X_BOARD;i++){
        for(int j=0;j<Y_BOARD;j++){
            int alive_neighbours=0;
            if(board[i-1][j-1]==1){
                alive_neighbours++;
            }
            if(board[i][j-1]==1){
                alive_neighbours++;
            }
            if(board[i+1][j-1]==1){
                alive_neighbours++;
            }
            if(board[i-1][j]==1){
                alive_neighbours++;
            }
            if(board[i+1][j]==1){
                alive_neighbours++;
            }
            if(board[i-1][j+1]==1){
                alive_neighbours++;
            }
            if(board[i][j+1]==1){
                alive_neighbours++;
            }
            if(board[i+1][j+1]==1){
                alive_neighbours++;
            }

            if(board[i][j] == 1){ // if cell alive
                if(alive_neighbours<2 || alive_neighbours > 3){ // Cell dies because of underpopulation or overpopulation
                    new_board[i][j] = 0; //cell dies
                }
           }else { // dead cells
                if(alive_neighbours == 3){
                    new_board[i][j]=1; //dead cell lives
                }
           }
        }
    }
}

int main(){
    int board[X_BOARD][Y_BOARD];

    inicializeBoard(board);
    int new_board[X_BOARD][Y_BOARD];
    memcpy(&new_board, &board, X_BOARD*Y_BOARD*sizeof(board[0][0]));
    
    printBoard(board);
    for(int i=0;i<10000;i++){
        checkCellNeighbours(board, new_board);
        memcpy(&board, &new_board, X_BOARD*Y_BOARD*sizeof(board[0][0]));
        
        printf("\033[2J");        /*  clear the screen  */
        printf("\033[H"); 
        usleep(110000);
        printBoard(board);

    }




    return 0;
}
