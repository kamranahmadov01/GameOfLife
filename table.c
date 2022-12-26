#include "table.h"

struct Table *generateTable(unsigned rows, unsigned cols) {
    struct Table *table = (struct Table *)malloc(sizeof(struct Table));
    if (table == NULL) 
        return NULL;

    table->rows = rows;
    table->cols = cols;

    table->matrix = (bool **)calloc(rows, sizeof(bool *));
    if (table->matrix == NULL) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < rows; ++i) {
        table->matrix[i] = (bool *)calloc(cols, sizeof(bool));
        if (table->matrix[i] != NULL)
            continue;

        for (int j = 0; j < i; ++j)
            free(table->matrix[j]);
        return NULL;
    }

    return table;
}

void fillRandom(struct Table *table, double density) {
    if (table == NULL || table->matrix == NULL)
        return;

    for (int i = 0; i < table->rows; ++i) {
        for (int j = 0; j < table->cols; ++j) {
            bool randomValue = (double)(rand() % 100) / 100 <= density;
            table->matrix[i][j] = randomValue;
        }
    }
}

void printTable(struct Table *table) {
    if (table == NULL || table->matrix == NULL)
        return;
    
    for (int i = 0; i < table->rows; ++i) {
        for (int j = 0; j < table->cols; ++j)
            printf("%s ", table->matrix[i][j] ? "X" : " ");
        printf("\n");
    }
}

void updateTable(struct Table *table) {
    if (table == NULL || table->matrix == NULL)
        return;
    
    struct Table *newTable = generateTable(table->rows, table->cols);
    if (newTable == NULL)
        return;
    
    for (int i = 0; i < table->rows; ++i) {
        for (int j = 0; j < table->cols; ++j) {
            int count = 0;
            for (int row = -1; row <= 1; ++row)
                for (int col = -1; col <= 1; ++col)
                    if (table->matrix[(i + row + table->rows) % table->rows][(j + col + table->cols) % table->cols])
                        ++count;

            if (table->matrix[i][j] && (count < 2 || count > 3))
                newTable->matrix[i][j] = false;
            else if (!table->matrix[i][j] && count == 3)
                newTable->matrix[i][j] = true;
            else
                newTable->matrix[i][j] = table->matrix[i][j];
        }
    }

    clearTable(table);

    table->rows = newTable->rows;
    table->cols = newTable->cols;

    for (int i = 0; i < table->rows; ++i)
        for (int j = 0; j < table->cols; ++j)
            table->matrix[i][j] = newTable->matrix[i][j];
}

void clearTable(struct Table *table) {
    if (table == NULL || table->matrix == NULL)
        return;

    table->rows = 0;
    table->cols = 0;

    for (int i = 0; i < table->rows; ++i) {
        if (table->matrix[i] != NULL) {
            free(table->matrix[i]);
            table->matrix[i] = NULL;
        }
    }
}
