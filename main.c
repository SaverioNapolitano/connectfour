#include "connectfour.h"


int main(void) {
    struct matrix m = {.rows=6, .cols=7};
    m.data = calloc(m.rows * m.cols, sizeof(int));
    int choice=0;
    printf("Which mode would you like to play?\n");
    printf("1: Against another player\n");
    printf("2: Against computer (easy mode)\n");
    printf("3: Against computer (hard mode)\n");
    printf("Insert the number of the mode\n");
    scanf("%i", &choice);
    while (choice<1 || choice>3){
        printf("Number not valid, try again\n");
        scanf("%i", &choice);
    }
    ConnectFour(&m, choice);

    free(m.data);
    return EXIT_SUCCESS;
}
