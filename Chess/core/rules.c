/// @file rules.c 

#include <Chess/core/rules.h>
#include <GLFW/glfw3.h>

static struct Board board; static struct Piece piece;

bool is_select_pieces(struct Piece self, double w, double h)
{
        glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        piece = self;

        // A : Press
        // B : Release

        // A -> B return true
        

        if(glfwGetMouseButton(window_get().handle, GLFW_MOUSE_BUTTON_LEFT))
        {
                if(glms_aabb_events(piece.buffer_position_data, piece.index, w, h, 576) && piece.index >= 8 && piece.index <= 15)
                {
                        return true;
                };

                if(glms_aabb_events(piece.buffer_position_data, piece.index, w, h, 576) && piece.index >= 24 && piece.index <= 32)
                {
                        return true;
                };
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

        if(glfwGetMouseButton(window_get().handle, GLFW_MOUSE_BUTTON_LEFT)){

                for(int i = 8;i <= 15;i ++){
                        if(glms_aabb_events(piece.buffer_position_data, i, w, h, 576)){
                                if(board.index == 2*8 + (i-8)|| board.index == 3*8 + (i-8) )
                                {
                                        return true;
                                };
                        };
                };

                for(int i = 24;i <= 32;i ++){
                        if(glms_aabb_events(piece.buffer_position_data, i, w, h, 576)){
                                if(board.index == 6*8 + (i-24)|| board.index == 5*8 + (i-24) )
                                {
                                        return true;
                                };
                        };
                };

        }

        return false;
};