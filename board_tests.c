/**
 * 
 * compile with: gcc -Wall board_tests.c ../board/board.c -lcunit
 * 
 * */
#include "../board/board.h"
#include "CUnit/Basic.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void test_new_circular_board(void){
    Board board = new_board(CIRCULAR);
    CU_ASSERT(board.type == CIRCULAR);
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            CU_ASSERT(board.cell[i][j] == DEAD);
}

void test_new_clipped_board(void){
    Board board = new_board(CLIPPED);
    CU_ASSERT(board.type == CLIPPED);
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            CU_ASSERT(board.cell[i][j] == DEAD);
}

void test_blinker_alv_ngbhrs(void){
    Board board = new_board(CLIPPED);
    /* blinker */
    board.cell[2][1] = ALIVE;
    board.cell[2][2] = ALIVE;
    board.cell[2][3] = ALIVE;
    CU_ASSERT(count_alive_neighbours(board, 2, 2) == 2);
    CU_ASSERT(count_alive_neighbours(board, 2, 1) == 1);
    CU_ASSERT(count_alive_neighbours(board, 2, 3) == 1);

    CU_ASSERT(count_alive_neighbours(board, 1, 2) == 3);
    CU_ASSERT(count_alive_neighbours(board, 3, 2) == 3);
}

void test_blinker_pass_day(void){
    Board board = new_board(CLIPPED);
    /* blinker */
    board.cell[2][1] = ALIVE;
    board.cell[2][2] = ALIVE;
    board.cell[2][3] = ALIVE;

    board = pass_day(board);

    CU_ASSERT(board.cell[2][3] == DEAD);
    CU_ASSERT(board.cell[2][1] == DEAD);

    CU_ASSERT(board.cell[1][2] == ALIVE);
    CU_ASSERT(board.cell[2][2] == ALIVE);
    CU_ASSERT(board.cell[3][2] == ALIVE);
}

void test_block_pass_day(void){
    Board board = new_board(CLIPPED);
    /* block */
    board.cell[1][2] = ALIVE;
    board.cell[1][1] = ALIVE;
    board.cell[2][2] = ALIVE;
    board.cell[2][1] = ALIVE;

    board = pass_day(board);

    CU_ASSERT(board.cell[1][2] == ALIVE);
    CU_ASSERT(board.cell[1][1] == ALIVE);
    CU_ASSERT(board.cell[2][2] == ALIVE);
    CU_ASSERT(board.cell[2][1] == ALIVE);
}

void test_blinker_circular(){
    Board board = new_board(CIRCULAR);
    /* blinker on the edge */
    board.cell[0][1] = ALIVE;
    board.cell[0][0] = ALIVE;
    board.cell[0][BOARD_WIDTH - 1] = ALIVE;

    board = pass_day(board);

    CU_ASSERT(board.cell[0][1] == DEAD);
    CU_ASSERT(board.cell[0][BOARD_WIDTH - 1] == DEAD);

    CU_ASSERT(board.cell[1][0] == ALIVE);
    CU_ASSERT(board.cell[0][0] == ALIVE);
    CU_ASSERT(board.cell[BOARD_HEIGHT - 1][0] == ALIVE);
}

int main(int argc, char const *argv[]){
    CU_pSuite pSuite1 = NULL;

    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add suite1 to registry
    pSuite1 = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
    if (pSuite1 == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite1, "Testing test_new_circular_board() function: \n", test_new_circular_board)) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite1, "Testing test_new_clipped_board() function: \n", test_new_clipped_board)) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }


    if ((CU_add_test(pSuite1, "Testing test_blinker_alv_ngbhrs() function: \n", test_blinker_alv_ngbhrs)) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite1, "Testing test_blinker_pass_day() function: \n", test_blinker_pass_day)) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests(); // OUTPUT to the screen
    CU_cleanup_registry(); // cleaning the Registry
    return CU_get_number_of_failures();
}