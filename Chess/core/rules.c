/// @file rules.c 

#include <Chess/core/rules.h>

bool is_select_pieces(float (*buffer_position_data)[8], int piece_index, double w, double h, int scale)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        if(glms_aabb_events(buffer_position_data, piece_index, w, h, window_get().y)){
            return true;
        };

        return false;
};

bool is_possible_moves(float (*buffer_position_data)[8], int board_index, double w, double h, int scale)
{
         glfwGetCursorPos(window_get().handle, &w, &h);

        h = glm_max(0,h);   
        w = glm_max(0,w);

        h = fabs(h - 576);

        if(glms_aabb_events(buffer_position_data, board_index, w, h, window_get().y)){
            return true;
        };

        return false;
};