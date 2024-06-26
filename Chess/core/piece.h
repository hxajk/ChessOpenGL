
#ifdef __cplusplus
extern "C" {
#endif


#include <Chess/gfx/vao.h>
#include <Chess/gfx/vbo.h>
#include <Chess/gfx/shader.h>
#include <Chess/gfx/texture.h>
#include <Chess/gfx/window.h>

#include <cglm/cglm.h>

#ifndef PIECE_H
#define PIECE_H

struct Piece {

  struct Shader shader_vertex;
  struct  VBO index_vertex;

  struct  VBO buffer_vertex[32];
  struct  VAO array_vertex[32];
  struct Texture texture_vertex[12];

  
  unsigned int index_data[6];
};

struct Piece piece_init();

void piece_render(struct Piece self);

void piece_destroy(struct Piece self);

#endif

#ifdef __cplusplus
    }
#endif