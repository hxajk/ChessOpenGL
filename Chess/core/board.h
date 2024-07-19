
#ifdef __cplusplus
extern "C" {
#endif

#include <Chess/gfx/vao.h>
#include <Chess/gfx/vbo.h>
#include <Chess/gfx/shader.h>
#include <Chess/gfx/texture.h>
#include <Chess/gfx/window.h>

#include <Chess/util/data.h>
#include <cglm/cglm.h>
#ifndef BOARD_H
#define BOARD_H

struct Board {
  struct Shader shader_vertex;
  struct  VBO index_vertex;

  struct  VBO buffer_vertex[8][8];
  struct  VAO array_vertex[8][8];
  
  float buffer_position_data[8][8][8];
  unsigned int index_data[6];

  float scale;
  double cx,cy;
};

struct Board board_init();

void board_get_info(struct Board* board);

void board_render(struct Board self);

void board_destroy(struct Board self);

#endif

#ifdef __cplusplus
  }
#endif