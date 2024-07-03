/// @file rules.c 

#include <Chess/core/rules.h>

static struct Board board; static struct Piece piece;
static int board_index;    static int piece_index;

bool is_select_possible_move(double w, double h)
{
        return true;
};

bool is_select_pieces(struct Piece self, int i, double w, double h)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        piece = self;
        piece_index = i;

        return false;
};

bool is_possible_moves(struct Board self, int i, double w, double h)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        board = self;
        board_index = i;

        return false;
};