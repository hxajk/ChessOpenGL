/*

   ____ _                      ___                    ____ _     
  / ___| |__   ___  ___ ___   / _ \ _ __   ___ _ __  / ___| |    
 | |   | '_ \ / _ \/ __/ __| | | | | '_ \ / _ \ '_ \| |  _| |    
 | |___| | | |  __/\__ \__ \ | |_| | |_) |  __/ | | | |_| | |___ 
  \____|_| |_|\___||___/___/  \___/| .__/ \___|_| |_|\____|_____|
                                   |_|                           

-- Author: hxajk (hxajkzzz@gmail.com).
-- Update: 2024-06-20 15:12:00 
*/

///////////////////////////////////////////////////////////////
#include "Chess/core/board.h"
#include "Chess/core/piece.h"
/////////////////////////////////////////////////////////////


void run(int width, int height, const char* title);

int main(int argc, char *argv[])
{
    run(1024,568,"Chess");
};

void run(int width, int height, const char* title)
{
    if(!glfwInit()){
        return;
    }

    Window window = window_init(width, height, title); 

    Board board = board_init();

    /* Piece piece = piece_init(); */


    while (!glfwWindowShouldClose(window.handle)) {
        board_render(board);
        /* piece_render(piece); */
        window_render(window);
    }

};