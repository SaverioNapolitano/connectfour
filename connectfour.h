//
// Created by Saverio Napolitano on 12/03/23.
//

#ifndef CONNECTFOUR2_CONNECTFOUR_H
#define CONNECTFOUR2_CONNECTFOUR_H
#include <stdlib.h>
#include <stdbool.h>
struct matrix
{
    size_t rows, cols;
    int* data;
};
extern void PrintGrid(struct matrix* m);
extern bool IsMoveValid(struct matrix* m, size_t c);
extern bool Win(struct matrix* m, int value);
extern size_t GetPlayerMove(struct matrix*m);
extern void Place(struct matrix* m, int value, size_t c);
extern void ConnectFour(struct matrix* m);
#endif //CONNECTFOUR2_CONNECTFOUR_H
