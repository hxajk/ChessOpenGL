
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

static inline bool glms_aabb_events(float position_data[8], double x, double y) {
  if (
      x >= 0 && 
      position_data[1] >= y && position_data[3] >= y && // y - (UP LEFT - UP RIGHT) 
      position_data[5] <= y && position_data[7] <= y && // y - (DOWN LEFT - DOWN RIGHT) 
      position_data[0] <= x && position_data[2] >= x && // x - (UP LEFT - UP RIGHT)
      position_data[4] >= x && position_data[6] <= x && // x - (DOWN LEFT - DOWN RIGHT)
      x <= BOARD_SIZE) {
    return true;
  };
  return false;
};

#endif

#ifdef __cplusplus
    }
#endif