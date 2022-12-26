#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Table {
    unsigned rows;
    unsigned cols;

    bool **matrix;
};

struct Table *generateTable(unsigned rows, unsigned cols);
void fillRandom(struct Table *table, double density);
void printTable(struct Table *table);
void updateTable(struct Table *table);
void clearTable(struct Table *table);
