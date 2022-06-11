#include "board.h"

/// @file board.c
/// @param board defines Board struct.

Board new_board(enum TYPE type){
    
    /// @brief Generates a @p board 
    /// @returns new board
    
    Board board;
    board.type = type;
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            board.cell[i][j] = DEAD;
    return board;
}

Board randomize_board(Board board){
    
    /// @brief Generates a cell on random position on the @p board
    /// @returns board with cells, which start acting from random position.
    /// @note @p srand(time(NULL)) and @p rand() functions are used to implement randomization.

    srand(time(NULL)); // seed rand
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            board.cell[i][j] = rand() & 1;
    return board;
}

unsigned count_alive_neighbours(Board board, unsigned i, unsigned j){

    /// @brief This function counts the number of alive neighbours of the cell in the given coordinate according to its @p board.type.
    /// @brief By checking conditions, function determines died cells and alive ones to move along.
    /// @param alive_neighbours is of integer type. It stores the number of available cells (alive neighbors) of a cell.
    /// @returns the number of alive neighbours.

    int alive_neighbours = 0;
    if(board.type == CIRCULAR){ // circular version
        if(i == 0) i = BOARD_HEIGHT;
        if(j == 0) j = BOARD_WIDTH;

        if(board.cell[i - 1][j - 1] == ALIVE) alive_neighbours++;
        if(board.cell[i - 1][j % BOARD_WIDTH] == ALIVE) alive_neighbours++;
        if(board.cell[i - 1][(j + 1) % BOARD_WIDTH] == ALIVE) alive_neighbours++;

        if(board.cell[i % BOARD_HEIGHT][j - 1] == ALIVE) alive_neighbours++;
        if(board.cell[i % BOARD_HEIGHT][(j + 1) % BOARD_WIDTH] == ALIVE) alive_neighbours++;

        if(board.cell[(i + 1) % BOARD_HEIGHT][j - 1] == ALIVE) alive_neighbours++;
        if(board.cell[(i + 1) % BOARD_HEIGHT][j % BOARD_WIDTH] == ALIVE) alive_neighbours++;
        if(board.cell[(i + 1) % BOARD_HEIGHT][(j + 1) % BOARD_WIDTH] == ALIVE) alive_neighbours++;
    }
    else { // clipped
        if(i != 0){
            if(j != 0)
                if(board.cell[i - 1][j - 1]) alive_neighbours++;

            if(board.cell[i - 1][j]) alive_neighbours++;

            if(j + 1 != BOARD_WIDTH)
                if(board.cell[i - 1][j + 1]) alive_neighbours++;
        }

        if(j != 0)
            if(board.cell[i][j - 1]) alive_neighbours++;
        if(j + 1 != BOARD_WIDTH)
            if(board.cell[i][j + 1]) alive_neighbours++;

        if(i + 1 != BOARD_HEIGHT){
            if(j != 0)
                if(board.cell[i + 1][j - 1]) alive_neighbours++;

            if(board.cell[i + 1][j]) alive_neighbours++;

            if(j != BOARD_WIDTH - 1)
                if(board.cell[i + 1][j + 1]) alive_neighbours++;
        }

    }

    return alive_neighbours;
}

Board pass_day(Board board){

    /// @brief This function checks whether the neighbour cell is alive or dead.
    /// @returns board with moving cells.

    static int temp_board[BOARD_HEIGHT][BOARD_WIDTH]; // static for making initial value 0 i.e DEAD

    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++){
            
            unsigned alive_neighbours = count_alive_neighbours(board, i, j);

            // -------------

            if(board.cell[i][j] == ALIVE){ 
                if(alive_neighbours < 2 || alive_neighbours > 3 ) 
                    temp_board[i][j] = DEAD; // die as if under/over population
                else
                    temp_board[i][j] = ALIVE;
            }
            else{ // if cell is dead
                if(alive_neighbours == 3) 
                    temp_board[i][j] = ALIVE; // become alive
                else
                    temp_board[i][j] = DEAD;
            }
        }
    
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            board.cell[i][j] = temp_board[i][j];

    return board;
}

void print_board(Board board){

    /// This function shows cells on the @p board

    // hide cursor
    printf("\033[2J");
    // goto 0,0
    printf("\033[0;0H");

    for (int i = 0; i < BOARD_HEIGHT; i++){
        // goto i+1,0
        printf("\033[%d;0H", i + 1);
        for (int j = 0; j < BOARD_WIDTH; j++) // two spaces for cell
            printf("%s  " BG_RESET, board.cell[i][j] == ALIVE ? BG_BLACK : BG_WHITE);
    }

    //show cursor
    printf("\033[?25h");
    printf("\n");
}

void console_run(Board board){

    /// @brief This function runs the program on the console and updates it with 0.5 seconds interval.

    while (true){
        print_board(board);
        board = pass_day(board);
        usleep(500 * 1000); // sleep 0.5 seconds
    }
}
