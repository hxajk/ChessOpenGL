

#include <Chess/gfx/vao.h>
#include <Chess/gfx/vbo.h>
#include <Chess/gfx/shader.h>
#include <Chess/gfx/window.h>

#include <cglm/cglm.h>

#ifndef PIECE_H
#define PIECE_H

struct Piece {
  struct  VBO buffer_vertex;
  struct  VBO index_vertex;
  struct  VAO array_vertex;
  struct Shader shader_vertex;
  
  float buffer_data[8];
  unsigned int index_data[6];
};

struct Piece piece_init();

void piece_render(struct Piece self);

void piece_destroy(struct Piece self);

#endif