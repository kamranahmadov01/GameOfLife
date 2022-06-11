#include "gui.h"

SDL_Event event;

void gui_run(Board board){
    SDL_Window* window = SDL_CreateWindow(
        "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_HEIGHT,
        SCREEN_WIDTH,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    while(!quit){
        for (int i = 0; i < BOARD_HEIGHT; i++){
            for (int j = 0; j < BOARD_WIDTH; j++){
                if(board.cell[i][j] == ALIVE)
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black for alive cells
                else // dead
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 ); // white for dead cells

                SDL_Rect r = {
                    SCREEN_HEIGHT / BOARD_HEIGHT * i, 
                    SCREEN_WIDTH / BOARD_WIDTH * j, 
                    SCREEN_HEIGHT / BOARD_HEIGHT, 
                    SCREEN_WIDTH / BOARD_WIDTH
                };
                SDL_RenderFillRect( renderer, &r );
            }
        }
        SDL_RenderPresent(renderer);
        board = pass_day(board);

        usleep(500 * 1000); // sleep 0.5 seconds
        while(SDL_PollEvent(&event))
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        board.cell[x * BOARD_HEIGHT / SCREEN_HEIGHT][y * BOARD_WIDTH / SCREEN_WIDTH] = ALIVE;
                    }
                    break;
            }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}