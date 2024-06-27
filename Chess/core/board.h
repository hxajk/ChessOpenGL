
#ifdef __cplusplus
extern "C" {
#endif

#include <Chess/gfx/vao.h>
#include <Chess/gfx/vbo.h>
#include <Chess/gfx/shader.h>
#include <Chess/gfx/window.h>

#include <cglm/cglm.h>
#ifndef BOARD_H
#define BOARD_H

struct Board {
  struct  VBO buffer_vertex;
  struct  VBO index_vertex;
  struct  VAO array_vertex;
  struct Shader shader_vertex;
  
  float buffer_data[8];
  unsigned int index_data[6];
};

struct Board board_init();

void board_render(struct Board self);

void board_destroy(struct Board self);

#endif

#ifdef __cplusplus
  }
#endif