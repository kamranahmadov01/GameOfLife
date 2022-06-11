#if !defined(__BOARD_H__)
#define __BOARD_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BG_BLACK "\033[40m"
#define BG_WHITE "\033[47m"
#define BG_RESET "\033[0m"

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 30

typedef enum {false, true} bool;

/// @file board.h
/// This is a header file for board.c file. It contains included libraries, macros, structures and function declarations.

/*! Struct Board has 2 variables. 
 * - enumerable @p 'type', \n 
 *   can be circular or clipped
 * - enumerable 2D array @p 'cell[][]', \n
 *   defined of height and width \n 
 *   can be dead or alive.
 */

typedef struct {
    enum TYPE { CIRCULAR, CLIPPED } type;
    enum { DEAD, ALIVE } cell[BOARD_HEIGHT][BOARD_WIDTH];
} Board;

Board new_board(enum TYPE type);

Board randomize_board(Board board);

unsigned count_alive_neighbours(Board board, unsigned i, unsigned j);

Board pass_day(Board board);

void print_board(Board board);

void console_run(Board board);

#endif // __BOARD_H__
