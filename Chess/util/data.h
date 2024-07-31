#ifdef __cplusplus
extern "C" {
#endif

#include <Chess/util/parser.h>
#include <cglm/cglm.h>
#include <Chess/util/util.h>

#ifndef DATA_H
#define DATA_H

extern vec4 fen_inital_data[32];
extern vec4 fen_dynamic_data[32];

/**
 * @brief Initalize fen data together.
 * 
 * @param position 
 * @param piece 
 */
void init_fen_data(vec2 position, vec2 piece);

/**
 * @brief Load fen data
 * 
 * @param fen 
 */

void load_fen_data(const char* fen);

/**
 * @brief Set the position data object in clockwise order
 * @param self.buffer_position_data 
 * @param start 
 * @param end 
 * @param y 
 * @param self.scale 
 */

void set_position_data(float buffer_position_data[POSITIONS_PER_PIECE], vec2 vertex_position, int y, float scale);

/**
 * @brief Simply set wether they're having the same value or not.
 * 
 * @param data_1 
 * @param data_2 
 * @return true 
 * @return false 
 */

bool is_equality_data(float data_1[8], float data_2[8]);

#endif

#ifdef __cplusplus
  }
#endif