#ifdef __cplusplus
extern "C" {
#endif

#include <Chess/core/board.h>

#include <cglm/cglm.h>
#include <Chess/gfx/gfx.h>

#ifndef MODULE_H
#define MODULE_H
#include <Chess/core/piece.h>
void highlight_selected_piece(int piece_index, int colour_piece, int value_piece, vec2 inital_position);
void translate_selected_piece(struct Board board, int piece_index, int selected_piece_index , bool isHolded);
#endif

#ifdef __cplusplus
  }
#endif