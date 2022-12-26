#include <stdio.h>

#include "setup.h"
#include "table.h"

int main() {
    setup();

    const unsigned rows = 10, cols = 10;
    struct Table *table = generateTable(rows, cols);
    if (table == NULL) {
        puts("Coudln't reserve any memory.");
        return -1;
    }

    fillRandom(table, 0.3);

    while (true) {
        printTable(table);
        updateTable(table);
        sleep(1);
        clear;
    }

    return 0;
}