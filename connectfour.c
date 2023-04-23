//
// Created by Saverio Napolitano on 12/03/23.
//

#include "connectfour.h"
/* To do:

	GUI;
	some more test;
	optimization;

*/

/**
 * prints the actual grid
 * @param m matrix to print
 */
void PrintGrid(struct matrix* m) {
    for (int r = 0; r < m->rows; ++r) {
        printf("+--+--+--+--+--+--+--+\n|");
        for (int c = 0; c < m->cols; ++c) {
            printf(" %d|", m->data[r * m->cols + c]);
        }
        printf("\n");
    }
    printf("+--+--+--+--+--+--+--+\n");
    printf("  0  1  2  3  4  5  6\n");
}
/**
 * checks if the move can be done
 * @param m matrix that represents the grid
 * @param c column chosen by the user
 * @return true if the move can be done, otherwise false
 */
bool IsMoveValid(struct matrix* m, int c) {
    if (c >= m->cols || c < 0) {
        printf("Error: Column not valid.\n");
        return false;
    }
    int i = c;
    while (1) {
        if (m->rows * m->cols - (m->cols - c) < i) {
            printf("Error: column full.\n");
            return false;
        }
        if (m->data[c] == 0) {
            return true;
        }
        i += m->cols;
    }
}
/**
 * gets the move done by the player
 * @param m matrix that represents the grid
 * @return the column chosen by the player
 */
int GetPlayerMove(struct matrix *m) {
    printf("Your turn: choose the column you would like to put your piece in.\n");
    int c = 0;
    int n = scanf("%i", &c);
    if (n != 1)
        return c;
    while(!IsMoveValid(m, c)){
        printf("Your turn: choose the column you would like to put your piece in.\n");
        n = scanf("%i", &c);
        if (n != 1)
            return c;
    }
    return c;
}
/**
 * checks if there are 4 connected tokens in the specified column
 * @param m the matrix that represents the grid
 * @param i the column to check
 * @param value the user who moved
 * @return true if the player has placed 4 connected tokens, otherwise false
 */
static bool CheckOneCol(struct matrix* m, int i, int value) {
    int count = 0;
    int c = i;
    while (i <= m->rows * m->cols - (m->cols - c)) {
        if (m->data[i] == value) {
            ++count;
        }
        else {
            count = 0;
        }
        if (count == 4) {
            return true;
        }
        i += m->cols;
    }
    return false;
}
/**
 * checks if in any of the columns there are 4 connected tokens
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @return true if a column has 4 connected tokens, otherwise false
 */
static bool CheckCols(struct matrix* m, int value) {
    for (int i = 0; i < m->cols; ++i) {
        if (CheckOneCol(m, i, value)) {
            return true;
        }
    }
    return false;
}
/**
 * checks if there are 4 connected tokens in the specified row
 * @param m the matrix that represents the grid
 * @param i the row to check
 * @param value the user who moved
 * @return true if the player has placed 4 connected tokens, otherwise false
 */
static bool CheckOneRow(struct matrix* m, int i, int value) {
    int r = i;
    int count = 0;
    while (i < (r+1) * m->cols) {
        if (m->data[i] == value) {
            ++count;
        }
        else {
            count = 0;
        }
        if (count == 4) {
            return true;
        }
        i++;
    }
    return false;
}
/**
 * checks if in any of the rows there are 4 connected tokens
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @return true if a row has 4 connected tokens, otherwise false
 */
static bool CheckRows(struct matrix* m, int value) {
    for (int i = 0; i < m->rows; ++i) {
        if (CheckOneRow(m, i, value)) {
            return true;
        }
    }
    return false;
}
/**
 * checks if there is a superior diagonal made of 4 connected token
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @param r_start the row to start from checking
 * @param c_start the colum to start from checking
 * @return true if there's a superior diagonal made of 4 connected tokens, otherwise false
 */
static bool SupDiagonal(struct matrix* m, int value, int r_start, int c_start) {

    for (int i = 0; i < 4; ++i) {
        if (m->data[r_start * m->cols + c_start] != value)
            return false;
        r_start--;
        c_start++;
    }
    return true;
}
/**
 * checks if there is an inferior diagonal made of 4 connected token
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @param r_start the row to start from checking
 * @param c_start the colum to start from checking
 * @return true if there's an inferior diagonal made of 4 connected tokens, otherwise false
 */
static bool InfDiagonal(struct matrix* m, int value, int r_start, int c_start) {

    for (int i = 0; i < 4; ++i) {
        if (m->data[r_start * m->cols + c_start] != value)
            return false;
        r_start++;
        c_start++;
    }
    return true;
}
/**
 * checks if there's any diagonal with 4 connected tokens
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @return true if there's a diagonal with 4 connected tokens, otherwise false
 */
static bool CheckDiagonal(struct matrix* m, int value) {
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < m->rows; ++r) {
            if (r < 3) {
                if (InfDiagonal(m, value, r, c))
                    return true;
            }
            else {
                if (SupDiagonal(m, value, r, c))
                    return true;
            }
        }
    }
    return false;
}
/**
 * checks if a user has won
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @return true if the user won, otherwise false
 */
bool Win(struct matrix* m, int value) {
    if (CheckCols(m, value) || CheckRows(m, value) || CheckDiagonal(m, value))
        return true;
    return false;
}
/**
 * places the token in the grid
 * @param m the matrix that represents the grid
 * @param value the user who moved
 * @param c the column chosen by the user
 */
void Place(struct matrix* m, int value, int c) {
    int r = m->rows;
    while (m->data[r * m->cols - (m->cols - c)] != 0) {
        r--;
    }

    m->data[r * m->cols - (m->cols - c)] = value;
}

/**
 * gets the move made by the computer
 * @param m the matrix that represents the grid
 * @return the column chosen by the computer
 */
static int GetComputerMove(struct matrix*m){
    int c = rand() % (m->cols + 1);
    while(!IsMoveValid(m, c)){
        c = rand() % (m->cols + 1);
    }
    return c;
}
/**
 * checks if the first player has won
 * @param m the matrix that represents the grid
 * @param mode the mode chosen by the user
 * @return true if the first player won, otherwise false
 */
static bool FirstPlayerWin(struct matrix *m, int mode){
    while (1) {
        printf("Player 1\n");
        int c = GetPlayerMove(m);
        Place(m, 1, c);
        PrintGrid(m);
        if (Win(m, 1)) {
            return true;
        }
        if(mode == 1){
            printf("Player 2\n");
            c = GetPlayerMove(m);
        } else {
            printf("Computer\n");
            c = GetComputerMove(m);
        }
        Place(m, 2, c);
        PrintGrid(m);
        if(mode != 1){
            printf("Computer placed in column %d\n", c);
        }
        if (Win(m, 2)) {
            return false;
        }
    }
}
/**
 * allows two players to have a connect four game
 * @param m the matrix that represents the grid
 */
void ConnectFourTwoPlayers(struct matrix* m) {
    PrintGrid(m);
    bool victory1 = FirstPlayerWin(m, 1);
    if (!victory1) {
        printf("Player 2 won.\nPress any key to close the program.\n");
        int c;
        scanf("%d", &c);
        return;
    }
    printf("Player 1 won.\nPress any key to close the program.\n");
}

/**
 * allows a player to have a connect four game against the computer that moves randomly
 * @param m the matrix that represents the grid
 */
void ConnectFourComputerEasyMode(struct matrix*m){
    srand(time(NULL));
    PrintGrid(m);
    bool victory1 = FirstPlayerWin(m, 2);
    if (!victory1) {
        printf("Computer won.\nPress any key to close the program.\n");
        int c;
        scanf("%d", &c);
        return;
    }
    printf("Player 1 won.\nPress any key to close the program.\n");

}
/**
 * selects the mode to be played according to the input received
 * @param m the matrix that represents the grid
 * @param choice the choice made by the player
 */
void ConnectFour(struct matrix *m, int choice){
    switch (choice) {
        case 1:
            ConnectFourTwoPlayers(m);
            break;
        case 2:
            ConnectFourComputerEasyMode(m);
            break;
        /*case 3:
            ConnectFourComputerHardMode(m);
            break;*/
    }
}
