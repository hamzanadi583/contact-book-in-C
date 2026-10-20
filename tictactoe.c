#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

void resetBoard() {
    char original[3][3] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = original[i][j]; 
        }
    }
}

char player = 'X';

int choice;

int count = 0;

int selectedChoices[9] = {};

bool win = false;

void printCurrentBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        
        if (i < 2) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
}

void checkWin() {
    for(int i = 0; i < 3 ; i++) {
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                    win = true;
                }
                else if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                    win = true;
                }
                else if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
                    win = true;
                }
                else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
                    win = true;
                }
            }
}


int main() {

    char playAgain = 'y';


    while (count < 9 && win == false){
        int *ch = &choice;
        char *p = &player;
        
        printf("Players take turn by choosing a number (1-9) \n");
        printCurrentBoard();
        printf("Player %c's turn \n", player);
        printf("Choice : ");
        scanf("%d", ch);
        printf("player %c's choice is %d\n",player,choice);

        selectedChoices[count] = choice;
        for (int i = 0; i < count; i++) {
            if (selectedChoices[i] == choice) {
                printf("Choice %d has already been selected, please choose another number \n", choice);
                count--;
                printf("Choice : ");
                scanf("%d", ch);
                
            }
        }

        char cchh = *ch + '0';
        for (int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 3 ; j++) {
                if (cchh == board[i][j])
                {
                    board[i][j] = player;
                    break;
                } 
            }
        }

        checkWin();

        if (win == false) {
            if (player == 'X') {
                player = 'O';
            }
            else {
                player = 'X';
            }
        }
        
        if (win == true) {
            printCurrentBoard();

            printf("Player %c wins the game \n", player);

            printf("Do you want to play again? (y/n) : ");
            scanf(" %c", &playAgain);
            printf("\n----------------------------------------\n\n");
            if (playAgain == 'y' || playAgain == 'Y'){
                resetBoard();
                player = 'X';
                win = false;
                count = 0;
                memset(selectedChoices, 0, sizeof(selectedChoices));
                count--;
            }
            
        }
        if (win == false && count == 8) {
            printCurrentBoard();
            printf("Game is a draw \n");

            printf("Do you want to play again? (y/n) : ");
            scanf(" %c", &playAgain);
            printf("\n----------------------------------------\n\n");
            if (playAgain == 'y' || playAgain == 'Y'){
                resetBoard();
                player = 'X';
                win = false;
                count = 0;
                memset(selectedChoices, 0, sizeof(selectedChoices));
                count--;
            }
        }
        count++;
    }

}