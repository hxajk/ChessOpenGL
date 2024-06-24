
#include <Chess/gfx/vao.h>
#include <Chess/gfx/vbo.h>
#include <Chess/gfx/shader.h>
#include <Chess/gfx/window.h>

#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Board {
  struct  VBO buffer_vertex;
  struct  VBO index_vertex;
  struct  VAO array_vertex;
  struct Shader shader_vertex;
  
  // TODO: Try to make this work on C

  std::vector<unsigned int> index_data;
  std::vector<float> buffer_data;

};

struct Board board_init();

void board_render(struct Board self);

#endif