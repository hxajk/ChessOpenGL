/// @file rules.c 

#include <Chess/core/rules.h>
#include <stdio.h>

static struct Board board; static struct Piece piece;

bool is_select_possible_move(double w, double h)
{
        printf("%d \n", board.index);
        return false;
};

bool is_select_pieces(struct Piece self, double w, double h)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        piece = self;

        if(is_select_possible_move(w, h))
        {
                return true;
        };

        return false;
};

bool is_possible_moves(struct Board self, double w, double h)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        board = self;

        if(is_select_possible_move(w, h))
        {
                return true;
        };

        return false;
};