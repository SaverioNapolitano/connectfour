//
// Created by Saverio Napolitano on 12/03/23.
//

#ifndef CONNECTFOUR2_CONNECTFOUR_H
#define CONNECTFOUR2_CONNECTFOUR_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
struct matrix
{
    int rows, cols;
    int* data;
};
extern void PrintGrid(struct matrix* m);
extern bool IsMoveValid(struct matrix* m, int c);
extern bool Win(struct matrix* m, int value);
extern int GetPlayerMove(struct matrix*m);
extern void Place(struct matrix* m, int value, int c);
extern void ConnectFourTwoPlayers(struct matrix* m);
extern void ConnectFour(struct matrix *m, int choice);
extern void ConnectFourComputerEasyMode(struct matrix*m);
extern void ConnectFourComputerHardMode(struct matrix*m);
#endif //CONNECTFOUR2_CONNECTFOUR_H
