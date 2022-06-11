#include "board.h"
#include "gui.h"

// this is main function
int main(int argc, char const *argv[]){
    char board_type_opt, ini_opt, if_opt;
    printf(
        "Welcome to Conway's game of life!\n"
        "[1] Clipped\n"
        "[2] Circular\n"
        "Choose board type: "
    );
    board_type_opt = getchar();
    if(board_type_opt != '1' && board_type_opt != '2'){
        perror("Invalid option... Exitting...\n");
        return -1;
    }
    Board board = new_board((board_type_opt == '1') ? CLIPPED:CIRCULAR);
    printf(
        "[1] GUI\n"
        "[2] Console\n"
        "Choose interface type: "
    ); getchar(); // to consume leading space
    if_opt = getchar(); 
    if(if_opt != '1' && if_opt != '2'){
        perror("Invalid option... Exitting...\n");
        return -1;
    }
    printf(
        "[1] Random\n"
        "[2] Blinker\n"
        "[3] Glider\n"
        "Choose initial board state: "
    );  getchar(); // to consume leading space
    ini_opt = getchar();
    switch (ini_opt){
        case '1':
            board = randomize_board(board);
            break;
        case '2':
            /* blinker */
            board.cell[2][1] = ALIVE;
            board.cell[2][2] = ALIVE;
            board.cell[2][3] = ALIVE;
            break;

        case '3':
            /* glider */
            board.cell[1][1] = ALIVE;
            board.cell[2][2] = ALIVE;
            board.cell[2][3] = ALIVE;
            board.cell[3][1] = ALIVE;
            board.cell[3][2] = ALIVE;
            break;

        default:
            perror("Invalid option... Exitting...\n");
            return -1;
    }

    if(if_opt == '1') // gui
        gui_run(board);
    else 
        console_run(board);
    return 0;
}
