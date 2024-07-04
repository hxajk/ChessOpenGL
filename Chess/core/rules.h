
#ifdef __cplusplus
extern "C" {
#endif

#ifndef RULES_H 
#define RULES_H 

#include <Chess/gfx/gfx.h>
#include <Chess/gfx/window.h>

#include <Chess/core/piece.h>
#include <Chess/core/board.h>

#include <Chess/util/util.h>
#include <Chess/util/aabb.h>

#include <cglm/cglm.h>

bool is_select_pieces(struct Piece self,  double w, double h);
bool is_possible_moves(struct Board self,  double w, double h);

#endif

#ifdef __cplusplus
    }
#endif