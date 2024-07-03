
#ifdef __cplusplus
extern "C" {
#endif

#include <Chess/util/util.h>
#include <Chess/util/aabb.h>
#include <Chess/gfx/gfx.h>
#include <Chess/gfx/window.h>

#include <cglm/cglm.h>
#ifndef RULES_H 
#define RULES_H 

bool is_select_pieces(float buffer_position_data[PIECE_LIMITS][POSITIONS_PER_PIECE],int piece_index,  double w, double h, int scale);
bool is_possible_moves(float buffer_position_data[BOARD_SIZE][POSITIONS_PER_SQUARE] ,int board_index,  double w, double h, int scale);

#endif

#ifdef __cplusplus
    }
#endif