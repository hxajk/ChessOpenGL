
#ifdef __cplusplus
extern "C" {
#endif

#ifndef AABB_H
#define AABB_H
#include <Chess/gfx/gfx.h>
#include <Chess/util/util.h>

/**
 * @brief A function return true whether it met the aabb collision requirements.
 * 
 * @param buffer_position_data 
 * @param i 
 * @param w 
 * @param h 
 * @param window_y 
 * @return true 
 * @return false 
 */

static inline bool glms_aabb_events(float buffer_position_data[256][8],int i, int x, int y, int window_y) {
  if (
      x >= 0 && 
      buffer_position_data[i][1] >= y && buffer_position_data[i][3] >= y && // y - (UP LEFT - UP RIGHT) 
      buffer_position_data[i][5] <= y && buffer_position_data[i][7] <= y && // y - (DOWN LEFT - DOWN RIGHT) 
      buffer_position_data[i][0] <= x && buffer_position_data[i][2] >= x && // x - (UP LEFT - UP RIGHT)
      buffer_position_data[i][4] >= x && buffer_position_data[i][6] <= x && // x - (DOWN LEFT - DOWN RIGHT)
      x <= window_y) {
    return true;
  };
  return false;
};

#endif

#ifdef __cplusplus
    }
#endif