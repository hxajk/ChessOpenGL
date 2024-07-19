#ifdef __cplusplus
extern "C" {
#endif

#include <cglm/cglm.h>
#include <Chess/util/util.h>

#ifndef DATA_H
#define DATA_H

/**
 * @brief Set the position data object in clockwise order
 * @param self.buffer_position_data 
 * @param start 
 * @param end 
 * @param y 
 * @param self.scale 
 */

static void set_position_data(float buffer_position_data[POSITIONS_PER_PIECE], vec2 vertex_position, int y, float scale) {
    for (int j = 0; j < POSITIONS_PER_PIECE; j++) {
        buffer_position_data[j] = scale * ((j & 1) == 1 ? ((j <= 3) ? y : y - 1) : ((j == 0 || j == 6) ? vertex_position[0] : vertex_position[1]));
    }
}

/**
 * @brief Simply set wether they're having the same value or not.
 * 
 * @param data_1 
 * @param data_2 
 * @return true 
 * @return false 
 */

static bool is_equality_data(float data_1[8], float data_2[8]) {
    for (int i = 0; i < 8; i++) {
        if (data_1[i] != data_2[i]) return false;
    }
    return true;
}

#endif

#ifdef __cplusplus
  }
#endif