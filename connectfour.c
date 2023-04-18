//
// Created by Saverio Napolitano on 12/03/23.
//

#include "connectfour.h"
#include <stdio.h>
/* To do:

	GUI;
	some more test;
	optimization;

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

static bool CheckCols(struct matrix* m, int value) {
    for (int i = 0; i < m->cols; ++i) {
        if (CheckOneCol(m, i, value)) {
            return true;
        }
    }
    return false;
}

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

static bool CheckRows(struct matrix* m, int value) {
    for (int i = 0; i < m->rows; ++i) {
        if (CheckOneRow(m, i, value)) {
            return true;
        }
    }
    return false;
}

static bool SupDiagonal(struct matrix* m, int value, int r_start, int c_start) {

    for (int i = 0; i < 4; ++i) {
        if (m->data[r_start * m->cols + c_start] != value)
            return false;
        r_start--;
        c_start++;
    }
    return true;
}

static bool InfDiagonal(struct matrix* m, int value, int r_start, int c_start) {

    for (int i = 0; i < 4; ++i) {
        if (m->data[r_start * m->cols + c_start] != value)
            return false;
        r_start++;
        c_start++;
    }
    return true;
}

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

bool Win(struct matrix* m, int value) {
    if (CheckCols(m, value) || CheckRows(m, value) || CheckDiagonal(m, value))
        return true;
    return false;
}

void Place(struct matrix* m, int value, int c) {
    int r = m->rows;
    while (m->data[r * m->cols - (m->cols - c)] != 0) {
        r--;
    }

    m->data[r * m->cols - (m->cols - c)] = value;
}

void ConnectFour(struct matrix* m) {
    PrintGrid(m);
    bool victory1;
    while (1) {
        printf("Player 1\n");
        int c = GetPlayerMove(m);
        Place(m, 1, c);
        PrintGrid(m);
        if (Win(m, 1)) {
            victory1 = true;
            break;
        }
        printf("Player 2\n");
        c = GetPlayerMove(m);
        Place(m, 2, c);
        PrintGrid(m);
        if (Win(m, 2)) {
            victory1 = false;
            break;
        }
    }
    if (!victory1) {
        printf("Player 2 won.\nPress any key to close the program.\n");
        int c;
        scanf("%d", &c);
        return;
    }
    printf("Player 1 won.\nPress any key to close the program.\n");
}
