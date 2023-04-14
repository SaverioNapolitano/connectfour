#include "connectfour.h"


int main(void) {
    struct matrix m = {.rows=6, .cols=7};
    m.data = calloc(m.rows * m.cols, sizeof(int));

    ConnectFour(&m);

    free(m.data);
    return EXIT_SUCCESS;
}
